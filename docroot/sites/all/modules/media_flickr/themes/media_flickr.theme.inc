<?php
/**
 * @file
 * Theme functions for the Media: Flickr module.
 */

function theme_media_flickr_preview_style($variables) {
  $variables['uri'] = media_flickr_variable_get('preview_uri');
  return theme('media_flickr_embed', $variables);
}

function theme_media_flickr_styles($variables) {
  $style = $variables['style'];
  $variables['file'] = $variables['object'];
  $variables['uri'] = $variables['object']->uri;
  $variables['style_name'] = $style['name'];
  return theme('media_flickr_embed', $variables);
}

function media_flickr_preprocess_media_flickr_photoset(&$variables) {
  // Build the URL for display.
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parts = $wrapper->get_parameters();
  $variables['user_id'] = drupal_encode_path($parts['u']);
  $variables['set_id'] = drupal_encode_path($parts['s']);
  $variables['width'] = isset($variables['width']) ? $variables['width'] : media_flickr_variable_get('width');
  $variables['height'] = isset($variables['height']) ? $variables['height'] : media_flickr_variable_get('height');
}

function theme_media_flickr_embed($variables) {
  if(isset($variables['preset']) && isset($variables['object'])){
    //get preset information from the variables object
    $preset_name = $variables[(string)'preset'];
    $all_presets = $variables[(string)'presets'];

    $preset = array(
      'effects' => $all_presets[(string)'presets'][(string)$preset_name],
    );

    // Build the URL for display.
    $uri = $variables['uri'];
    $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
    $parts = $wrapper->get_parameters();

    $width = $height = 0;

    foreach ($preset['effects'] as $effect) {
      switch ($effect['name']) {
        case 'resize':
          $width = isset($effect['settings']['width']) ? $effect['settings']['width'] : NULL;
          $height = isset($effect['settings']['height']) ? $effect['settings']['height'] : NULL;
          break;
      }
    }
    if (isset($variables['object']->override)) {
      $override = $variables['object']->override;
      if (isset($override['width'])) {
        $width = $override['width'];
      }
      if (isset($override['height'])) {
        $height = $override['height'];
      }
    }

    $attributes = array();
    if ($width) {
      $attributes['width'] = $width;
    }
    if ($height) {
      $attributes['height'] = $height;
    }

    // If this is a photoset, then return the flash object for that.
    if (!isset($parts['p']) && isset($parts['s'])) {
      $attributes['uri'] = $uri;
      return theme('media_flickr_photoset', $attributes);
    }

    $output = theme('image', array(
      'path' => media_flickr_image_url($parts['p'], $width, $height),
      'alt' => $variables['alt'],
      'title' => $variables['title'],
      'attributes' => $attributes,
      'getsize' => FALSE,
    ));
    return $output;
  }
}

function theme_media_flickr_field_formatter_styles($variables) {
  $element = $variables['element'];
  $style = $variables['style'];
  $variables['file'] = $element['#item'];
  $variables['uri'] = $variables['file']['uri'];
  $variables['style_name'] = $style['name'];
  return theme('media_flickr_embed', $variables);
}
