<?php
// $Id: textsize.block.inc,v 1.5 2010/06/03 21:43:03 christianzwahlen Exp $

/**
 * @file
 * block, page and theme functions.
 */

/**
 * Returns an array of allowed values.
 *
 * @return
 *   An array of allowed values.
 */
function textsize_allowed_values() {
  $ts_in = variable_get('textsize_increment', 6);
  $ts_no = variable_get('textsize_normal', 76);
  $ts_mi = variable_get('textsize_minimum', 50);
  $ts_ma = variable_get('textsize_maximum', 150);
  $textsize_allowed_values = array();
  if (is_numeric($ts_in) && is_numeric($ts_no) && is_numeric($ts_mi) && is_numeric($ts_ma)) {
    if ($ts_in >= 1 && $ts_no >= 1 && $ts_mi >= 1 && $ts_ma >= 3) {
      $ts_st = ($ts_no - (floor((($ts_no - $ts_mi) / $ts_in)) * $ts_in));
      $ts_en = ($ts_no + (floor((($ts_ma - $ts_no) / $ts_in)) * $ts_in));
      for ($value = $ts_st; $value <= $ts_en; $value = $value + $ts_in ) {
        $textsize_allowed_values[] = $value;
      };
    }
  }
    return $textsize_allowed_values;
}

/**
 * Cookie expires.
 *
 * @return
 *   The cookie expires in seconds.
 */
function textsize_cookie_expires($mode = 'php') {
  $textsize_cookie_expires = variable_get('textsize_cookie_expires', 365) ;
  $output = ($textsize_cookie_expires * 24 * 60 * 60);
  if ($mode == 'js') {
    $output = $textsize_cookie_expires;
  }
  return $output;
}

/**
 * Menu callback; increase the textsize, then redirects to the previous page.
 */
function textsize_increase() {
  $textsize_cookie_expires = textsize_cookie_expires($mode = 'php');
  $textsize_cookie_domain = variable_get('textsize_cookie_domain', base_path());
  $textsize_link_type = variable_get('textsize_link_type', 'variable');
  $ts_in = variable_get('textsize_increment', 6);
  $ts_no = variable_get('textsize_normal', 76);
  $ts_ma = variable_get('textsize_maximum', 150);
  $textsize_maximum = ($ts_no + (floor((($ts_ma - $ts_no) / $ts_in)) * $ts_in));
  $textsize_normal_display = textsize_display($ts_no, 0);
  $textsize_maximum_display = textsize_display($textsize_maximum, 0);
  $textsize_message = variable_get('textsize_message', 1);
  $textsize_post = array();
  $textsize_cookie = array();
  $textsize_cookie['textsize'] = NULL;
  // allowed values
  $textsize_allowed = textsize_allowed_values();
  // check the type and the content
  if (in_array($_COOKIE['textsize'], $textsize_allowed)) {
    $textsize_cookie['textsize'] = (int) filter_xss($_COOKIE['textsize']);
  }
  // calculation of text size
  $ts_value = (($textsize_cookie['textsize'] + $ts_in));
  $ts_value_display = textsize_display($ts_value, 0);
  // set session/cookie
  if (!isset($_COOKIE['textsize']) && $textsize_message == 1) {
    drupal_set_message(t('The text size have not been saved, because your browser do not accept cookies.'), 'error');
  }
  elseif ($textsize_link_type == 'fix' && $textsize_cookie['textsize'] == ($ts_no - $ts_in) && $textsize_message == 1) {
    drupal_set_message(t('The text size maximum is: %ts_max%.', array('%ts_max' => textsize_display(($ts_no + $ts_in), 0))), 'error');  }
  elseif (($textsize_cookie['textsize'] == $textsize_maximum) && (variable_get('textsize_reset', 0) == 1)) {
    $_SESSION['textsize'] = $ts_no;
    setcookie("textsize", $ts_no, time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size maximum is: %ts_max%.', array('%ts_max' => $textsize_maximum_display)), 'warning');
      drupal_set_message(t('The text size have been saved as %textsize_normal%.', array('%textsize_normal' => $textsize_normal_display)));
    }
  }
  elseif (($textsize_cookie['textsize'] == $textsize_maximum) && $textsize_message == 1) {
    drupal_set_message(t('The text size maximum is: %ts_max%.', array('%ts_max' => $textsize_maximum_display)), 'error');
  }
  elseif ($textsize_link_type == 'fix' && $textsize_cookie['textsize'] == $ts_no || $textsize_link_type == 'fix' && $textsize_cookie['textsize'] == ($ts_no + $ts_in)) {
    $_SESSION['textsize'] = ($ts_no + $ts_in);
    setcookie("textsize", ($ts_no + $ts_in), time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size have been saved as %ts_value%.', array('%ts_value' => textsize_display(($ts_no + $ts_in), 0))));
    }
  }
  else {
    $_SESSION['textsize'] = $ts_value;
    setcookie("textsize", $ts_value, time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size have been saved as %ts_value%.', array('%ts_value' => $ts_value_display)));
    }
  }
  textsize_clear_cache();
  drupal_goto();
}

/**
 * Menu callback; decrease the textsize, then redirects to the previous page.
 */
function textsize_decrease() {
  $textsize_cookie_expires = textsize_cookie_expires($mode = 'php');
  $textsize_cookie_domain = variable_get('textsize_cookie_domain', base_path());
  $textsize_link_type = variable_get('textsize_link_type', 'variable');
  $ts_in = variable_get('textsize_increment', 6);
  $ts_no = variable_get('textsize_normal', 76);
  $ts_mi = variable_get('textsize_minimum', 50);
  $textsize_minimum = ($ts_no - (floor((($ts_no - $ts_mi) / $ts_in)) * $ts_in));
  $textsize_normal_display = textsize_display($ts_no, 0);
  $textsize_minimum_display = textsize_display($textsize_minimum, 0);
  $textsize_message = variable_get('textsize_message', 1);
  $textsize_post = array();
  $textsize_cookie = array();
  $textsize_cookie['textsize'] = NULL;
  // allowed values
  $textsize_allowed = textsize_allowed_values();
  // check the type and the content
  if (in_array($_COOKIE['textsize'], $textsize_allowed)) {
    $textsize_cookie['textsize'] = (int) filter_xss($_COOKIE['textsize']);
  }
  // calculation of text size
  $ts_value = (($textsize_cookie['textsize'] - $ts_in));
  $ts_value_display = textsize_display($ts_value, 0);
  // set session/cookie
  if (!isset($_COOKIE['textsize']) && $textsize_message == 1) {
    drupal_set_message(t('The text size have not been saved, because your browser do not accept cookies.'), 'error');
  }
  elseif ($textsize_link_type == 'fix' && $textsize_cookie['textsize'] == ($ts_no - $ts_in) && $textsize_message == 1) {
    drupal_set_message(t('The text size minimum is: %ts_min%.', array('%ts_min' =>  textsize_display(($ts_no - $ts_in), 0))), 'error');
  }
  elseif (($textsize_cookie['textsize'] == $textsize_minimum) && (variable_get('textsize_reset', 0) == 1)) {
    $_SESSION['textsize'] = $ts_no;
    setcookie("textsize", $ts_no, time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size minimum is: %ts_min%.', array('%ts_min' => $textsize_minimum_display)), 'warning');
      drupal_set_message(t('The text size have been saved as %textsize_normal%.', array('%textsize_normal' => $textsize_normal_display)));
    }
  }
  elseif (($textsize_cookie['textsize'] == $textsize_minimum) && $textsize_message == 1) {
    drupal_set_message(t('The text size minimum is: %ts_min%.', array('%ts_min' => $textsize_minimum)), 'error');
  }
  elseif ($textsize_link_type == 'fix' && $textsize_cookie['textsize'] == $ts_no || $textsize_link_type == 'fix' && $textsize_cookie['textsize'] == ($ts_no + $ts_in)) {
    $_SESSION['textsize'] = ($ts_no - $ts_in);
    setcookie("textsize", ($ts_no - $ts_in), time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size have been saved as %ts_value%.', array('%ts_value' => textsize_display(($ts_no - $ts_in), 0))));
    }
  }
  else {
    $_SESSION['textsize'] = $ts_value;
    setcookie("textsize", $ts_value, time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size have been saved as %ts_value%.', array('%ts_value' => $ts_value_display)));
    }
  }
  textsize_clear_cache();
  drupal_goto();
}

/**
 * Menu callback; change the textsize to normal, then redirects to the previous page.
 */
function textsize_normal() {
  $textsize_cookie_expires = textsize_cookie_expires($mode = 'php');
  $textsize_cookie_domain = variable_get('textsize_cookie_domain', base_path());
  $textsize_normal = variable_get('textsize_normal', 76);
  $textsize_normal_display = textsize_display($textsize_normal, 0);
  $textsize_message = variable_get('textsize_message', 1);
  // set session/cookie
  if (!isset($_COOKIE['textsize']) && $textsize_message == 1) {
    drupal_set_message(t('The text size have not been saved, because your browser do not accept cookies.'), 'error');
  }
  else {
    $_SESSION['textsize'] = $textsize_normal;
    setcookie("textsize", $textsize_normal, time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size have been saved as %textsize_normal%.', array('%textsize_normal' => $textsize_normal_display)));
    }
  }
  textsize_clear_cache();
  drupal_goto();
}

/**
 * Menu callback; change the textsize to the cookie value, then redirects to the previous page.
 */
function textsize_set() {
  $textsize_cookie_expires = textsize_cookie_expires($mode = 'php');
  $textsize_cookie_domain = variable_get('textsize_cookie_domain', base_path());
  $textsize_normal = variable_get('textsize_normal', 76);
  $textsize_message = variable_get('textsize_message', 1);
  $textsize_post = array();
  $textsize_cookie = array();
  // allowed values
  $textsize_allowed = textsize_allowed_values();
  // check the type and the content
  if (in_array($_COOKIE['textsize'], $textsize_allowed)) {
    $textsize_cookie['textsize'] = (int) filter_xss($_COOKIE['textsize']);
  }
  // set session/cookie
  if (!isset($_COOKIE['textsize']) && $textsize_message == 1) {
    drupal_set_message(t('The text size have not been saved, because your browser do not accept cookies.'), 'error');
  }
  elseif (isset($_COOKIE['textsize'])) {
    $_SESSION['textsize'] = $textsize_cookie['textsize'];
    setcookie("textsize", $textsize_cookie['textsize'], time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    if ($textsize_message == 1) {
      drupal_set_message(t('The text size have been saved as %textsize%.', array('%textsize' => textsize_display($textsize_cookie['textsize'], 0))));
    }
  }
  textsize_clear_cache();
  drupal_goto();
}

/**
 * Clear defined cache tables
 */
function textsize_clear_cache() {
  $tables = array(
    'cache_page',
    'cache_block',
  );
  foreach ($tables as $table) {
    cache_clear_all('*', $table, TRUE);
  }
}

/**
 * Block Title
 *
 * @return
 *   "Text Size" and "Current Size" or "Zoom" and "Current Zoom".
 *
 * @see textsize_admin_settings()
 */
function textsize_block_title($title = 'title') {
  $textsize_block_title = variable_get('textsize_block_title', 'text_size');
  $textsize_block_title_text = t('Text Size');
  $textsize_current_textsize_text = t('Current Size');
  switch ($textsize_block_title) {
    case 'zoom':
    $textsize_block_title_text = t('Zoom');
    $textsize_current_textsize_text = t('Current Zoom');
    break;
  }
  if ($title == 'title') {
    return $textsize_block_title_text;
  }
  elseif ($title == 'current') {
    return $textsize_current_textsize_text;
  }
}

/**
 * Returns an array of available values for the select element in the block text size.
 *
 * @return
 *   An array of available values, for selecting the text size.
 *
 * @see textsize_form()
 */
function textsize_block_form_options() {
  $textsize_link_type = variable_get('textsize_link_type', 'variable');
  $ts_in = variable_get('textsize_increment', 6);
  $ts_no = variable_get('textsize_normal', 76);
  $ts_mi = variable_get('textsize_minimum', 50);
  $ts_ma = variable_get('textsize_maximum', 150);
  if ($textsize_link_type == 'fix') {
    $ts_st = ($ts_no - $ts_in);
    $ts_en = ($ts_no + $ts_in);
  }
  elseif ($textsize_link_type == 'variable') {
    $ts_st = ($ts_no - (floor((($ts_no - $ts_mi) / $ts_in)) * $ts_in));
    $ts_en = ($ts_no + (floor((($ts_ma - $ts_no) / $ts_in)) * $ts_in));
  }
  $options = array();
  for ($value = $ts_st; $value <= $ts_en; $value = $value + $ts_in) {
    $options[$value] = textsize_display($value, 0);
  };
  return $options;
}

/**
 * Implement hook_form().
 *
 * Generate the select form for the block.
 *
 * @see textsize_block()
 */
function textsize_form($form, &$form_state) {
  $textsize_cookie_expires = textsize_cookie_expires($mode = 'php');
  $textsize_cookie_domain = variable_get('textsize_cookie_domain', base_path());
  $textsize_block_title = textsize_block_title($title = 'title');
  $textsize_normal = variable_get('textsize_normal', 76);
  $textsize_increment = variable_get('textsize_increment', 6);
  $textsize_minimum = variable_get('textsize_minimum', 50);
  $textsize_maximum = variable_get('textsize_maximum', 150);
  $textsize_message = variable_get('textsize_message', 1);
  $display_current_textsize = variable_get('textsize_display_current_textsize', 'display');
  $textsize_current = textsize_get_current($value = 'int');
  $options = textsize_block_form_options();
  $textsize_post = array();
  $textsize_cookie = array();
  // allowed values
  $textsize_allowed = textsize_allowed_values();
  // check the type and the content
  if (isset($_COOKIE['textsize']) && isset($_POST['textsize_select'])) {
    if (in_array($_POST['textsize_select'], $textsize_allowed)) {
      $textsize_post['textsize'] = (string) filter_xss($_POST['textsize_select']);
    }
    // set session/cookie
    if ($textsize_post['textsize'] <= $textsize_maximum && $textsize_post['textsize'] >= $textsize_minimum) {
      setcookie("textsize", $textsize_post['textsize'], time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
      $_SESSION['textsize'] = $textsize_post['textsize'];
      if ($textsize_message == 1) {
        drupal_set_message(t('The text size have been saved as %textsize_post%.', array('%textsize_post' =>  textsize_display($textsize_post['textsize'], 0))));
      }
      textsize_clear_cache();
    }
  }
  elseif (!isset($_COOKIE['textsize']) && isset($_POST['textsize_select']) && $textsize_message == 1) {
    drupal_set_message(t('The text size have not been saved, because your browser do not accept cookies.'), 'error');
  }
  $subtitle = NULL;
  if (variable_get('textsize_display_subtitle', 0) == 1) {
    $subtitle = $textsize_block_title;
  }
  $form = array();
  $form['textsize_select'] = array(
    '#type' => 'select',
    '#title' => $subtitle,
    '#name' => 'textsize_select',
    '#options' => $options,
    '#default_value' => variable_get('textsize_select', $textsize_current),
    '#weight' => 0,
    // '#description' => t('Select the text size.'),
  );
  $form['#attributes']['class'][] = 'textsize';
  $form['textsize_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 1,
  );
  $form['#skip_duplicate_check'] = TRUE;
  return $form;
}

/**
 * Implement theme().
 *
 * @see textsize_form()
 */
function theme_textsize_form($form) {
  $output = drupal_render($form);
  return $output;
}

/**
 * Implement hook_theme().
 */
function textsize_theme() {
  $variables = array(
    'dest' => NULL,
    'block_title' => NULL,
    'list_inline' => NULL,
    'current_inline' => NULL,
    'subtitle' => NULL,
    'subtitle_text' => NULL,
    'display_links' => NULL,
    'current_textsize' => NULL,
    'display_current_textsize' => NULL,
    'display_current_textsize_text' => NULL,
    'link_type' => NULL,
    'increment' => NULL,
    'normal' => NULL,
    'current_textsize_text' => NULL,
    'textsize' => NULL,
  );
  return array(
    'textsize_text' => array(
      'variables' => $variables,
      'template' => 'textsize-text',
    ),
    'textsize_image' => array(
      'variables' => $variables,
      'template' => 'textsize-image',
    ),
    'textsize_form' => array(
      'render element' => 'form',
      'template' => 'textsize-form',
    ),
  );
}

/**
 * Process variables for textsize-text.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $dest: The drupal function drupal_get_destination().
 * - $block_title: Block title: "Text Size" or "Zoom".
 * - $list_inline: Display the ul list "inline" or not.
 * - $current_inline: Display the current text size "inline" or not.
 * - $subtitle: The subtitle.
 * - $subtitle_text: "Text Size"/"Zoom" or inline "Text Size: "/"Zoom: ".
 * - $textsize_increase: The text size increase link.
 * - $textsize_decrease: The text size decrease link.
 * - $textsize_normal: The text size normal link.
 * - $display_links: Show or hide ("display_hidden") the text in the links.
 * - $current_textsize: The current text size.
 * - $display_current_textsize: Show or hide ("display_hidden") the text of the current textsize.
 * - $display_current_textsize_text: Show or hide ("display_hidden").
 * - $link_type: Return "variable" for variable or fix.
 * - $increment: The increment step (default 6%).
 * - $normal: The textsize normal (default 76%).
 * - $current_textsize_text: The current textsize text "Current Size" or "Current Zoom".
 * - $textsize: The current text size (default 100%).
 *
 * @see textsize_theme(), textsize-text.tpl.php
 */
function template_preprocess_textsize_text(&$variables) {
  $textsize_block_title = textsize_block_title($title = 'title');
  $textsize_current_textsize_text = textsize_block_title($title = 'current');
  $textsize_normal = variable_get('textsize_normal', 76);
  $textsize_increment = variable_get('textsize_increment', 6);
  $variables['template_files'][] = 'textsize-text';
  if (isset($variables['block'])) {
    $variables['template_files'][] = 'textsize-text';
  }
  $variables['dest'] = drupal_get_destination();
  $variables['block_title'] = $textsize_block_title;
  $variables['list_inline'] = "list";
  $subtitle_add = NULL;
  if (variable_get('textsize_display_list_inline', 0) == 1) {
    $variables['list_inline'] = "inline";
    $subtitle_add = ": ";
  }
  $variables['current_inline'] = "textsize_current_list";
  if (variable_get('textsize_display_current_inline', 0) == 1) {
    $variables['current_inline'] = "textsize_current_inline";
  }
  $variables['subtitle'] = NULL;
  $variables['subtitle_text'] = NULL;
  if (variable_get('textsize_display_subtitle', 0) == 1) {
    $variables['subtitle'] = "subtitle";
    $variables['subtitle_text'] = $textsize_block_title . $subtitle_add;
  }
  $variables['textsize_increase'] = NULL;
  if (variable_get('textsize_display_increase', 1) == 1) {
    $variables['textsize_increase'] = "textsize_increase";
  }
  $variables['textsize_decrease'] = NULL;
  if (variable_get('textsize_display_decrease', 1) == 1) {
    $variables['textsize_decrease'] = "textsize_decrease";
  }
  $variables['textsize_normal'] = NULL;
  if (variable_get('textsize_display_normal', 1) == 1) {
    $variables['textsize_normal'] = "textsize_normal";
  }
  $variables['display_links'] = "display";
  if (variable_get('textsize_display_links', 1) == 0) {
    $variables['display_links'] = "display_hidden";
  }
  $variables['current_textsize'] = NULL;
  $variables['display_current_textsize'] = "display";
  $variables['display_current_textsize_text'] = "display";
  switch (variable_get('textsize_display_current_text_value', 'text_value')) {
    case "text_value":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display";
      $variables['display_current_textsize_text'] = "display";
    break;
    case "value":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
    case "hidden":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display_hidden";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
    case "remove":
      $variables['display_current_textsize'] = "display_hidden";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
  }
  $variables['link_type'] = variable_get('textsize_link_type', 'variable');
  $variables['increment'] = textsize_display($textsize_increment, 0);
  $variables['normal'] = textsize_display($textsize_normal, 0);
  $variables['current_textsize_text'] = $textsize_current_textsize_text;
  $variables['textsize'] = textsize_get_current($value = 'display');
}

/**
 * Process variables for textsize-image.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $dest: The drupal function drupal_get_destination().
 * - $block_title: Block title: "Text Size" or "Zoom".
 * - $list_inline: Display the ul list "inline" or not.
 * - $current_inline: Display the current text size "inline" or not.
 * - $subtitle: The subtitle.
 * - $subtitle_text: "Text Size"/"Zoom" or inline "Text Size: "/"Zoom: ".
 * - $textsize_increase: The text size increase link.
 * - $textsize_decrease: The text size decrease link.
 * - $textsize_normal: The text size normal link.
 * - $display_links: Show or hide ("display_hidden") the text in the links.
 * - $current_textsize: The current text size.
 * - $display_current_textsize: Show or hide ("display_hidden") the text of the current textsize.
 * - $display_current_textsize_text: Show or hide ("display_hidden").
 * - $link_type: Return "variable" for variable or fix.
 * - $increment: The increment step (default 6%).
 * - $normal: The textsize normal (default 76%).
 * - $current_textsize_text: The current textsize text "Current Size" or "Current Zoom".
 * - $textsize: The current text size (default 100%).
 *
 * @see textsize_theme(), textsize-image.tpl.php
 */
function template_preprocess_textsize_image(&$variables) {
  $textsize_block_title = textsize_block_title($title = 'title');
  $textsize_current_textsize_text = textsize_block_title($title = 'current');
  $textsize_normal = variable_get('textsize_normal', 76);
  $textsize_increment = variable_get('textsize_increment', 6);
  $variables['template_files'][] = 'textsize-image';
  if (isset($variables['block'])) {
    $variables['template_files'][] = 'textsize-image';
  }
  $variables['dest'] = drupal_get_destination();
  $variables['block_title'] = $textsize_block_title;
  $variables['list_inline'] = "list";
  $subtitle_add = NULL;
  if (variable_get('textsize_display_list_inline', 0) == 1) {
    $variables['list_inline'] = "inline";
    $subtitle_add = ": ";
  }
  $variables['current_inline'] = "textsize_current_list";
  if (variable_get('textsize_display_current_inline', 0) == 1) {
    $variables['current_inline'] = "textsize_current_inline";
  }
  $variables['subtitle'] = NULL;
  $variables['subtitle_text'] = NULL;
  if (variable_get('textsize_display_subtitle', 0) == 1) {
    $variables['subtitle'] = "subtitle";
    $variables['subtitle_text'] = $textsize_block_title . $subtitle_add;
  }
  $variables['textsize_increase'] = NULL;
  if (variable_get('textsize_display_increase', 1) == 1) {
    $variables['textsize_increase'] = "textsize_increase";
  }
  $variables['textsize_decrease'] = NULL;
  if (variable_get('textsize_display_decrease', 1) == 1) {
    $variables['textsize_decrease'] = "textsize_decrease";
  }
  $variables['textsize_normal'] = NULL;
  if (variable_get('textsize_display_normal', 1) == 1) {
    $variables['textsize_normal'] = "textsize_normal";
  }
  $variables['display_links'] = "display";
  if (variable_get('textsize_display_links', 1) == 0) {
    $variables['display_links'] = "display_hidden";
  }
  $variables['current_textsize'] = NULL;
  $variables['display_current_textsize'] = "display";
  $variables['display_current_textsize_text'] = "display";
  switch (variable_get('textsize_display_current_text_value', 'text_value')) {
    case "text_value":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display";
      $variables['display_current_textsize_text'] = "display";
    break;
    case "value":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
    case "hidden":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display_hidden";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
    case "remove":
      $variables['display_current_textsize'] = "display_hidden";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
  }
  $variables['link_type'] = variable_get('textsize_link_type', 'variable');
  $variables['increment'] = textsize_display($textsize_increment, 0);
  $variables['normal'] = textsize_display($textsize_normal, 0);
  $variables['current_textsize_text'] = $textsize_current_textsize_text;
  $variables['textsize'] = textsize_get_current($value = 'display');
}

/**
 * Process variables for textsize-form.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $list_inline: Display the ul list "inline" or not.
 * - $current_inline: Display the current text size "inline" or not.
 * - $current_textsize: The current text size.
 * - $display_current_textsize: Show or hide ("display_hidden") the text of the current textsize.
 * - $display_current_textsize_text: Show or hide ("display_hidden").
 * - $textsize_form: The form.
 * - $current_textsize_text: The current textsize text "Current Size" or "Current Zoom".
 * - $textsize: The current text size (default 100%).
 *
 * @see textsize_theme(), textsize-form.tpl.php
 */
function template_preprocess_textsize_form(&$variables) {
  $textsize_current_textsize_text = textsize_block_title($title = 'current');
  $variables['textsize'] = array();
  $hidden = array();
  // Provide variables named after form keys so themers can print each element independently.
  foreach (element_children($variables['form']) as $key) {
    $type = $variables['form'][$key]['#type'];
    if ($type == 'hidden' || $type == 'token') {
      $hidden[] = drupal_render($variables['form'][$key]);
    }
    else {
      $variables['textsize'][$key] = drupal_render($variables['form'][$key]);
    }
  }
  $variables['list_inline'] = "list";
  if (variable_get('textsize_display_list_inline', 0) == 1) {
    $variables['list_inline'] = "inline";
  }
  $variables['current_inline'] = "textsize_current_list";
  if (variable_get('textsize_display_current_inline', 0) == 1) {
    $variables['current_inline'] = "textsize_current_inline";
  }
  $variables['current_textsize'] = NULL;
  $variables['display_current_textsize'] = "display";
  $variables['display_current_textsize_text'] = "display";
  switch (variable_get('textsize_display_current_text_value', 'text_value')) {
    case "text_value":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display";
      $variables['display_current_textsize_text'] = "display";
    break;
    case "value":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
    case "hidden":
      $variables['current_textsize'] = "current_textsize";
      $variables['display_current_textsize'] = "display_hidden";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
    case "remove":
      $variables['display_current_textsize'] = "display_hidden";
      $variables['display_current_textsize_text'] = "display_hidden";
    break;
  }
  // Hidden form elements have no value to themers. No need for separation.
  $variables['textsize']['hidden'] = implode($hidden);
  // Collect all form elements to make it easier to print the whole form.
  $variables['textsize_form'] = implode($variables['textsize']);
  $variables['current_textsize_text'] = $textsize_current_textsize_text;
  $variables['textsize'] = textsize_get_current($value = 'display');
}
