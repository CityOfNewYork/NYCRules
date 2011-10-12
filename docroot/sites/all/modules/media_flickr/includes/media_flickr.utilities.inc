<?php

/**
 *  @file
 *  Utility functions for Media: Flickr.
 */

/**
 *  Based on the Photo ID of a Flickr image, this will return the URL to the
 *  image itself.
 *  @param $photo_code
 *    The Flickr photo code.
 *  @param $width
 *  @param $height
 *    We use this to guess the actual size provided by Flickr.
 *  @param $cached
 *    If TRUE, then we'll cache the remote URL if the attempt to save the file
 *    locally fails.
 */
function _media_flickr_photo_url($photo_code, $width = 0, $height = 0, $cached = TRUE) {
  if ($photo_code) {
    $size = _media_flickr_guess_size($width, $height);
    return _media_flickr_photo_url_from_size($photo_code, $size);
  }
}

/**
 *  This returns a cached photo stream from the Flickr farm servers.
 */
function _media_flickr_photo_remote_url($photo_code, $size) {
  $getsize = _media_flickr_sets_request('flickr.photos.getSizes', array('photo_id' => $photo_code));

  if ($getsize && ($getsize['@attributes']['stat'] != 'fail')) {
    // For small images, there may not be the sizes 0..4 that
    // media_flickr_guess_size assumes, so:
    $size = min($size, count($getsize['sizes']['size'])-1);

    return $getsize['sizes']['size'][$size]['@attributes']['source'];
  }
}

/**
 *  This is a wrapper for emfield_request_xml that includes flickr's api key.
 *  @param string $method
 *  @param array $args
 *  @param boolean $refresh
 *    Optional; if TRUE, then we'll force a new load of the XML. Otherwise,
 *    a cached version will be retrieved if possible.
 *  @return object
 *    A fully populated SimpleXML object.
 */
function _media_flickr_sets_request($method, $args = array(), $refresh = FALSE) {
  // Display an error if we don't have an API key yet.
  if (!_media_flickr_error_check()) {
    return array();
  }

  $args['api_key'] = trim(media_flickr_variable_get('api_key'));
  if ($secret = trim(media_flickr_variable_get('api_secret'))) {
    $args['secret'] = md5($secret);
  }
  $args['method'] = $method;

  $xml = media_retrieve_xml(MEDIA_FLICKR_RESTPOINT . '?' . drupal_http_build_query($args), FALSE, $refresh);
  return $xml;
}

/**
 *  This will log an error if we don't have a key yet.
 *  In addition, if the user is an admin, we'll display an error.
 */
function _media_flickr_error_check() {
  static $checked;
  if (is_null($checked)) {
    if (media_flickr_variable_get('api_key') == '') {
      global $user;
      $error = 'You do not yet have a Flickr API key set. You will need to !apply and enter your key at the !settings before Flickr images may be displayed.';
      $arguments = array('!apply' => l(t('apply for a Flickr API key'), MEDIA_FLICKR_API_APPLICATION_URL), '!settings' => l(t('Flickr administration page'), 'admin/config/media/media_flickr'));
      if (user_access('administer site configuration')) {
        drupal_set_message(t($error, $arguments), 'error');
      }
      watchdog('media_flickr', $error, $arguments);
      $checked = FALSE;
    }
    else {
      $checked = TRUE;
    }
  }
  return $checked;
}

/**
 *  This will return the appropriate array key for the image size we wish.
 */
function _media_flickr_guess_size($width = 0, $height = 0) {
  $max = max($width, $height);

  if ($max) {
    foreach (array('0' => 75, '1' => 100, '2' => 240, '3' => 500, '4' => 1024) as $size => $value) {
      if ($max <= $value) {
        return $size;
      }
    }
  }

  // If we don't have width or height set, then get the original size.
  return '5';
}

function _media_flickr_photo_url_from_size($photo_code, $size = 5) {
  // Check to make sure we have a valid photo code.
  if (is_numeric($photo_code)) {
    $filepath = _media_flickr_photo_remote_url($photo_code, $size);
    // URLize that path...
    $filepath = url($filepath, array('absolute' => TRUE));
    return $filepath;
  }
}

/**
 *  Returns an array of all URLs for photos associated with a photoset,
 *  associated by photo code. These will be of the Flickr specified size (1-5),
 *  and may be local or remote, based on settings and availability.
 *
 *  @param $photoset
 *    The Flickr photoset id.
 *  @param $size
 *    Optional. A number from 1-5 (small to large).
 */
// function _media_flickr_photoset_load_photos($photoset, $size = 5) {
//   static $photosets;
//
//   if (is_null($photosets)) {
//     $photosets = array();
//   }
//
//   $id = $photoset['photoset']['id'];
//
//   // We cache our results in a static variable.
//   if (is_null($photosets[$id])) {
//     // Reset the array of photos.
//     $photosets[$id] = array();
//
//     // If we're allowed to store images locally, then grab the latest list
//     // of local URL's.
//     if ($store_local = variable_get('media_flickr_store_local', FALSE)) {
//       $results = db_query("SELECT z.code, f.filepath FROM {media_flickr_sets} s INNER JOIN {media_flickr_sizes} z ON z.code = s.code AND z.size = %d INNER JOIN {files} f ON f.fid = z.fid WHERE s.photoset = '%s'", $size, $photoset['photoset']['id']);
//       while ($result = db_fetch_object($results)) {
//         $photosets[$id][$result->code] = $result->filepath;
//       }
//     }
//
//     // @TODO: remove 'dead' photos from photoset...
//
//     // Ensure we have a URL for each photo in the photoset.
//     // This can be local or remote.
//     foreach ($photoset['photoset']['photo'] as $photo_code => $photo) {
//       // If we don't have a URL yet, grab one.
//       if (!isset($photosets[$id][$photo_code])) {
//         // If we're allowed to store local photos, then attempt to do so now.
//         if ($store_local) {
//           // First ensure we have the photo associated with this photoset.
//           if (!db_result(db_query("SELECT COUNT(*) FROM {media_flickr_sets} WHERE photoset = '%s' AND code = '%s'", $id, $photo_code))) {
//             // The photo is newly associated to this photoset. Put it in place.
//             $record = array(
//               'photoset' => $id,
//               'code' => $photo_code,
//             );
//             drupal_write_record('media_flickr_sets', $record);
//
//             // Now record the metadata associated with a photo.
//             media_flickr_record_photo($photo_code);
//
//             // Now we'll try to grab the URL manually, as it may have already
//             // been stored locally through another photoset. If not, this will
//             // attempt to fetch a photo and store it, or return the remote URL.
//             $photosets[$id][$photo_code] = media_flickr_photo_url_from_size($photo_code, $size);
//           }
//           else {
//             // We have the proper association; we just need this size photo.
//             // Hopefully we'll grab a local photo. If not, we'll get the remote.
//             $photosets[$id][$photo_code] = media_flickr_store_local($photo_code, $size);
//           }
//         }
//         else {
//           // Let's be happy with the remote URL.
//           $photosets[$id][$photo_code] = media_flickr_photo_remote_url($photo_code, $size);
//         }
//       }
//     }
//   }
//
//   return $photosets[$id];
// }
