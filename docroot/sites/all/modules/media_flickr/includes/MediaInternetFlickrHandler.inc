<?php

/**
 * @file
 * Define MediaInternetFlickrHandler class.
 */

class MediaInternetFlickrHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    $patterns = array(
      '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/([0-9]+)/in/photostream@i',
      '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/([0-9]+)/in/set-([0-9]+)@i',
      '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/([0-9]+)/?[^\? ]@i',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[1]) && isset($matches[2])) {
        return file_stream_wrapper_uri_normalize('flickr://u/' . $matches[1] . "/p/" . $matches[2]);
      }
    }
    $patterns = array(
      '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/sets/([0-9]+)@i',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[1]) && isset($matches[2])) {
        return file_stream_wrapper_uri_normalize('flickr://u/' . $matches[1] . "/s/" . $matches[2]);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function validate() {
    // @todo Media module currently fails when two files try to have the same
    //   URI, so catch that in the validation step. Some day, it would be nice
    //   to allow it, however. See http://drupal.org/node/952422.
    $uri = $this->parse($this->embedCode);
    $existing_files = file_load_multiple(array(), array('uri' => $uri));
    if (count($existing_files)) {
      throw new MediaInternetValidationException(t('You have entered a URL for a image that is already in your library.'));
    }
  }

  public function save() {
    $file = $this->getFileObject();
    file_save($file);
    return $file;
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    //@todo: this is terribly broken in some ways because the function is really
    // made for local files which are 'real'
    return file_uri_to_object($uri);
  }
}
