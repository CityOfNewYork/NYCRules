<?php
// $Id: textsize.admin.inc,v 1.10 2011/01/04 23:13:20 christianzwahlen Exp $

/**
 * @file
 * Provides the Text Size administrative interface.
 */

/**
 * Implement hook_help().
 */
function textsize_help($path, $arg) {
  $path_textsize =  base_path() . drupal_get_path('module', 'textsize');
  $abbr_php = '<abbr lang="en" xml:lang="en" title="' . t('PHP: Hypertext Preprocessor') . '">PHP</abbr>';
  $abbr_php_small = '<abbr lang="en" xml:lang="en" title="' . t('PHP: Hypertext Preprocessor') . '">php</abbr>';
  $abbr_mysql = '<abbr title="' . t('My Structured Query Language') . '">MySQL</abbr>';
  $abbr_xhtml = '<abbr lang="en" xml:lang="en" title="' . t('Extensible Hypertext Markup Language') . '">XHTML</abbr>';
  $abbr_css = '<abbr lang="en" xml:lang="en" title="' . t('Cascading Style Sheets') . '">CSS</abbr>';
  $abbr_css_small = '<abbr lang="en" xml:lang="en" title="' . t('Cascading Style Sheets') . '">css</abbr>';
  $abbr_wcag = '<abbr lang="en xml:lang="en" title="' . t('Web Content Accessibility Guidelines') . '">WCAG</abbr>';
  $abbr_bitv = '<abbr lang="de" xml:lang="de" title="' . t('Barrierefreie Informationstechnik-Verordnung') . '">BITV</abbr>';
  $abbr_png = '<abbr lang="en" xml:lang="en" title="' . t('Portable Network Graphics') . '">PNG</abbr>';
  $abbr_gif = '<abbr lang="en" xml:lang="en" title="' . t('Graphic Interchange Format') . '">GIF</abbr>';
  $abbr_svg = '<abbr lang="en" xml:lang="en" title="' . t('Scalable Vector Graphics') . '">SVG</abbr>';
  $abbr_xcf_small = '<abbr lang="en" xml:lang="en" title="' . t('eXperimental Computing Facility') . '">xcf</abbr>';
  $abbr_id = '<abbr lang="en" xml:lang="en" title="' . t('Identification') . '">ID</abbr>';
  $abbr_em = '<abbr lang="en" xml:lang="en" title="' . t('Equal measurement') . '">em</abbr>';
  $abbr_tpl_php = '<abbr title="' . t('PHP: Hypertext Preprocessor Template', array('!abbr_php' => $abbr_php)) . '">tpl.php</abbr>';
  $link_wcag = l(t('Web Content Accessibility Guidelines'), 'http://www.w3.org/TR/WCAG/', array('attributes' => array('title' => t('External link to:') . ' ' . t('Web Content Accessibility Guidelines'))));
  $link_bitv= l(t('Barrierefreie Informationstechnik-Verordnung'), 'http://bundesrecht.juris.de/bitv/anlage_8.html', array('attributes' => array('title' => t('External link to:') . ' ' . t('Barrierefreie Informationstechnik-Verordnung'))));
  $link_ff = l(t('Mozilla Firefox'), 'http://www.mozilla.com/en-US/firefox', array('attributes' => array('title' => t('External link to:') . ' ' . t('Mozilla Firefox'))));
  $link_ts_perm = l(t('Permissions'), 'admin/config/people/permissions', array('attributes' => array('title' => t('Text Size configuration')), 'fragment' => 'module-textsize'));
  $link_block = l(t('Blocks'), 'admin/structure/block', array('attributes' => array('title' => t('Text Size configuration'))));
  $link_ts_config = l(t('Text Size configuration'), 'admin/config/content/textsize', array('attributes' => array('title' => t('Text Size configuration'))));
  $link_po_import = l(t('Import'), 'admin/config/regional/translate/import', array('attributes' => array('title' => t('Translate interface') . ', ' . t('Import'))));
  $link_ts = l(t('Download Themes') . ': ' . t('Text Size home page'), 'http://www.zwahlendesign.ch/textsize', array('attributes' => array('title' => t('External link to:') . ' ' . t('Text Size home page'), 'class' => 'ts_download_button')));
  $link_ts_important = l(t('Overwrite text size in templates'), 'admin/config/content/textsize', array('attributes' => array('title' => t('Overwrite text size in templates')), 'fragment' => 'edit-textsize-important'));
  $link_jquery_cookie = l(t('jQuery plugins'), 'http://drupal.org/project/jquery_plugin');
  $link_footnote_1 = l('1', 'admin/help/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 1'), 'fragment' => 'footnote-1'));
  $link_footnote_2 = l('2', 'admin/help/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 2'), 'fragment' => 'footnote-2'));
  switch ($path) {
    case 'admin/help#textsize':
      $output = '<p><img src="' . $path_textsize . '/images/textsize_list.png" alt="' . t('Screenshot of block:') . ' ' . t('Select menu') . '." class="ts_float_right" />' . '</p>' . "\n";
      $output .= '<p>' . t('This module display a adjustable text size changer or a zoom function on the page for a better web accessibility.') . '</p>' . "\n";
      $output .= '<p>' . t('The zoom function is comparable to the text zoom function in Firefox 3, but this module resize also variable media objects, variable pixel images and vector images.')  . '</p>' . "\n";
      $output .= '<h3>' . t('Advantages compared with browser zoom') . '</h3>' . "\n";
      $output .= '<ol>' . "\n";
      $output .= '  <li><strong>' . t('Adjustable.') . '</strong> ' . t('Increases/decreases step, minimum, maximum, standard and variable or three fixed values.') . '</li>' . "\n";
      $output .= '  <li><strong>' . t('Resize region definable.') . '</strong> ' . t('For example a element with a !abbr_id "%content":', array('!abbr_id' => $abbr_id, '%content' => 'content')) . ' <br /><code lang="en">&lt;div id="content"&gt;CONTENT&lt;/div&gt;</code>.</li>' . "\n";
      $output .= '  <li><strong>' . t('Browser independent.') . '</strong></li>' . "\n";
      $output .= '  <li>' . t('One click function.') . ' ' . t('No tutorial required.') . '</li>' . "\n";
      $output .= '  <li>' . t('Same handling in any browser (shortcuts).') . '</li>' . "\n";
      $output .= '  <li>' . t('Resize text, variable images and media objects (media objects and pixel images with "!abbr_em" or "&#037;" size specification and !abbr_svg images).', array('!abbr_svg' => $abbr_svg, '!abbr_em' => $abbr_em)) . '</li>' . "\n";
      $output .= '  <li>' . t('Select menu availabe.') . '</li>' . "\n";
      $output .= '  <li>' . t('Display current text size (zoom size).') . '</li>' . "\n";
      $output .= '</ol>' . "\n";
      $output .= '<hr />' . "\n";
      $output .= '<h3>' . t('Features') . '</h3>' . "\n";
      $output .= '<p><img src="' . $path_textsize . '/images/textsize_select.png" alt="' . t('Screenshot of block:') . ' ' . t('Select menu') . '." class="ts_float_right" /></p>' . "\n";
      $output .= '<ul>' . "\n";
      $output .= '<li>' . t('!abbr_wcag and !abbr_bitv conform. More Information on: !link_wcag and !link_bitv.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv, '!link_wcag' => $link_wcag, '!link_bitv' => $link_bitv)) . ' ' . t('Keep the conditions:') . ' ' . "\n";
      $output .= '  <ol>' . "\n";
      $output .= '    <li>' . t('!abbr_wcag/!abbr_bitv 1.1: Short text equivalents for images.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</li>' . "\n";
      $output .= '    <li>' . t('!abbr_wcag/!abbr_bitv 3.1: Standard links with text without images in the source code.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</li>' . "\n";
      $output .= '    <li>' . t('!abbr_wcag/!abbr_bitv 6.3: No !javascript required.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv, '!javascript' => '<em lang="en">JavaScript</em>')) . '</li>' . "\n";
      $output .= '    <li>' . t('!abbr_wcag/!abbr_bitv 11.1: Open and standard code.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</li>' . "\n";
      $output .= '    <li>' . t('!abbr_wcag/!abbr_bitv 13.6: Links in a list.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</li>' . "\n";
      $output .= '  </ol>' . "\n";
      $output .= '</li>' . "\n";
      $output .= '<li>' . t('No !javascript required. !jquery suppport.', array('!javascript' => '<em lang="en">JavaScript</em>', '!jquery' => '<em lang="en">jQuery</em>')) . '</li>' . "\n";
      $output .= '<li>' . t('No !abbr_css required.', array('!abbr_css' => $abbr_css)) . '</li>' . "\n";
      $output .= '<li>' . t('Minimum and maximum text size.') . '</li>' . "\n";
      $output .= '<li>' . t('Caching mode: "Normal" and "Aggressive" compatible.') . '</li>' . "\n";
      $output .= '<li>' . t('Uniform markin of menu, based on the open source browser Firefox 2.0 (!link_ff).', array('!link_ff' => $link_ff)) . '</li>' . "\n";
      $output .= '<li>' . t('Block type') . ': ' . "\n";
      $output .= '<a href="' . $path_textsize . '/images/textsize_list.png" title="' . t('Screenshot of block:') . ' ' . t('Text Size') . ', ' . t('Text links') . '." >' . t('Text links') . '</a> [' . $link_footnote_1 . '], ';
      $output .= '<a href="' . $path_textsize . '/images/textsize_img.png" title="' . t('Screenshot of block:') . ' ' . t('Text Size') . ', ' . t('Image links') . '." >' . t('Image links') . '</a> [' . $link_footnote_2 . '], ';
      $output .= '<a href="' . $path_textsize . '/images/textsize_select.png" title="' . t('Screenshot of block:') . ' ' . t('Text Size') . ', ' . t('Select menu') . '." >' . t('Select menu') . '</a>.';
      $output .= '  </li>' . "\n";
      $output .= '<li>' . t('Themable.') . '</li>' . "\n";
      $output .= '</ul>' . "\n";
      $output .= '<p id="footnote-1">[1] ' . t('Images are showed with !abbr_css.', array('!abbr_css' => $abbr_css)) . ' <span class="ts_ok">' . t('Ideal for Web Accessibility.') . '</span></p>' . "\n";
      $output .= '<p id="footnote-2">[2] ' . t('No Link text, only images in the !abbr_xhtml source code with standard 0 pixel margin.', array('!abbr_xhtml' => $abbr_xhtml)) . ' <span class="warning">' . t('Warning') . ': ' . t('Not for: !abbr_wcag/!abbr_bitv 3.1! If !javascript is not activated: No image change action if the cursor move over the images!', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv, '!javascript' => '<em lang="en">JavaScript</em>')) . '</span></p>' . "\n";
      $output .= '<hr />' . "\n";

      // Drupal version specific
      $output .= '<h3>' . t('Requirements') . '</h3>' . "\n";
      $output .= '<ol>' . "\n";
      $output .= '  <li>Drupal 7.</li>' . "\n";
      $output .= '  <li>' . t('Theme or a theme region with font sitze "!abbr_em", "&#037;" or no sitze for the !internet_explorer browser.', array('!internet_explorer' => '<em lang="en">Internet Explorer</em>', '!abbr_em' => $abbr_em)) . '</li>' . "\n";
      $output .= '</ol>' . "\n";
      $output .= '<hr />' . "\n";
      $output .= '<h3>' . t('Settings') . '</h3>' . "\n";
      $output .= '<p><img src="' . $path_textsize . '/images/textsize_img.png" alt="' . t('Screenshot of block:') . ' ' . t('Image links') . '." class="ts_float_right" /></p>' . "\n";
      $output .= '<ol>' . "\n";
      $output .= '  <li>' . t('Go to:') . ' "' . t('Administer') . '", "' . t('Configuration and modules') . '", "' . t('People and permissions') . '", "' . $link_ts_perm . '" ("<em lang="en">admin/config/people/permissions#module-textsize</em>"). ' . t('Set the different roles.') . '</li>' . "\n";
      $output .= '  <li>' . t('Go to:') . ' "' . t('Administer') . '", "' . t('Structure') . '", "' . $link_block . '" ("<em lang="en">admin/structure/block</em>"). ' . t('Make the block "Text Size" visibile.') . '</li>' . "\n";
      $output .= '  <li>' . t('Go to:') . ' "' . t('Administer') . '", "' . t('Site configuration') . '", "' . t('Content authoring') . '", "' . $link_ts_config . '" ("<em lang="en">admin/config/content/textsize</em>"). ' . t('Change the settings if you want.') . '</li>' . "\n";
      $output .= '  <li>' . t('Go to:') . ' "' . t('Administer') . '", "' . t('Site building') . '", "' . t('Translate interface') . '", "' . $link_po_import . '" ("<em lang="en">admin/config/regional/translate/import</em>"). ' . t('Import your language file (for German "!de_po") if it is necessary.', array('!de_po' => '<em lang="en">' . drupal_get_path('module', 'textsize') . '/translations/<abbr lang="de" title="Deutsch">de</abbr>.<abbr title="PO translation file">po</abbr></em>')) . '</li>' . "\n";
      $output .= '</ol>' . "\n";
      $output .= '<hr />' . "\n";
      $output .= '<h3>' . t('Theming') . '</h3>' . "\n";
      $output .= '<h4>' . t('Create Themes') . '</h4>' . "\n";
      $output .= '<p><img src="' . $path_textsize . '/images/textsize_img2.png" alt="' . t('Screenshot of block:') . ' "' . t('Image links, not in a list') . '" class="ts_float_right" /></p>' . "\n";
      $output .= '<ol>' . "\n";
      $output .= '  <li>' . t('Copy the files/directorys in your theme:') . "\n";
      $output .= '    <ol>' . "\n";
      $output .= '      <li lang="en">textsize-text.' . $abbr_tpl_php . '</li>' . "\n";
      $output .= '      <li lang="en">textsize-image.' . $abbr_tpl_php . '</li>' . "\n";
      $output .= '      <li lang="en">textsize-form.' . $abbr_tpl_php . '</li>' . "\n";
      $output .= '      <li lang="en">textsize.' . $abbr_css_small . '</li>' . "\n";
      $output .= '      <li lang="en">images</li>' . "\n";
      $output .= '    </ol>' . "\n";
      $output .= '  </li>' . "\n";
      $output .= '  <li>' . t('Edit the !abbr_php and !abbr_css code in the files.', array('!abbr_php' => $abbr_php, '!abbr_css' => $abbr_css)) . ' ' . t('Example:') . ' ' . t('Image links, not in a list') . ': ' . t('Change the following elements:') . ' <del>&#060;ul&#062;/&#060;/ul&#062;</del> ' . t('to') . ': <ins>&#060;p&#062;/&#060;/p&#062;</ins><br /> <del>&#060;li&#062;&#060;/li&#062;</del> ' . t('to') . ': <ins>&#060;span class="display_hidden"&#062;&#160;&#124;&#160;&#060;/span&#062;</ins>.<br /><span class="info">' . t('!abbr_wcag/!abbr_bitv 10.5: Adjacent hyperlinks have to be separated by printable characters surrounded by spaces.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</span> <span class="warning">' . t('Warning') . ': ' . t('Not for: !abbr_wcag/!abbr_bitv 13.6! Links are not in a list.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</span></p>' . "\n";
      $output .= '  <li>' . t('Edit the !abbr_php templates (!abbr_tpl_php) and textsize.!abbr_css_small file.', array('!abbr_php' => $abbr_php, '!abbr_tpl_php' => $abbr_tpl_php, '!abbr_css_small' => $abbr_css_small)) . ' ' . t('Example:') . ' ' . t('Image links, not in a list') . ': ' . t('Change the following elements:') . ' <del>&#060;ul&#062;/&#060;/ul&#062;</del> ' . t('to') . ': <ins>&#060;p&#062;/&#060;/p&#062;</ins><br /> <del>&#060;li&#062;&#060;/li&#062;</del> ' . t('to') . ': <ins>&#060;span class="display_hidden"&#062;&#160;&#124;&#160;&#060;/span&#062;</ins>.<br /><span class="info">' . t('!abbr_wcag/!abbr_bitv 10.5: Adjacent hyperlinks have to be separated by printable characters surrounded by spaces.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</span> <span class="warning">' . t('Warning') . ': ' . t('Not for: !abbr_wcag/!abbr_bitv 13.6! Links are not in a list.', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv)) . '</span></p>' . "\n";
      $output .= '  <li>' . t('Edit the images. Create your own icons. The source file is in the directory:') . ' "<em lang="en">/images/source/textsize.' . $abbr_xcf_small . '</em>". ' .  t('!abbr_png images are for new browsers and !abbr_gif images for old browsers (!internet_explorer 6).', array('!abbr_png' => $abbr_png, '!abbr_gif' => $abbr_gif, '!internet_explorer' => '<em lang="en">Internet Explorer</em>')) . '</li>' . "\n";
      $output .= '</ol>' . "\n";
      // Drupal version specific end

      $output .= '<h4>' . t('Download Themes') . '</h4>' . "\n";
      $output .= '<p>' . t('Edited templates are available from the developers website:') . ' ' . $link_ts . '</p>' . "\n";
      $output .= '<hr />' . "\n";
      $output .= '<h3>' . t('Screenshots') . '</h3>' . "\n";
      $output .= '<p><img src="' . $path_textsize . '/images/textsize.png" alt="' . t('Text Size') . ' ' . t('Screenshots') . '." />' . '</p>' . "\n";
      $output .= '<hr />' . "\n";
      return $output;
    break;
  }
}

/**
 * Builds and returns the textsize settings form.
 *
 * @ingroup forms
 * @see textsize_admin_settings_validate()
 */
function textsize_admin_settings() {
  $abbr_php = '<abbr lang="en" xml:lang="en" title="' . t('PHP: Hypertext Preprocessor') . '">PHP</abbr>';
  $abbr_xhtml = '<abbr lang="en" xml:lang="en" title="' . t('Extensible Hypertext Markup Language') . '">XHTML</abbr>';
  $abbr_css = '<abbr lang="en" xml:lang="en" title="' . t('Cascading Style Sheets') . '">CSS</abbr>';
  $abbr_wcag = '<abbr lang="en xml:lang="en" title="' . t('Web Content Accessibility Guidelines') . '">WCAG</abbr>';
  $abbr_bitv = '<abbr lang="de" xml:lang="de" title="' . t('Barrierefreie Informationstechnik-Verordnung') . '">BITV</abbr>';
  $abbr_id = '<abbr lang="en" xml:lang="en" title="' . t('Identification') . '">ID</abbr>';
  $link_ts_important = l(t('Overwrite text size in templates'), 'admin/config/content/textsize', array('attributes' => array('title' => t('Overwrite text size in templates')), 'fragment' => 'edit-textsize-important'));
  $link_footnote_1 = l('1', 'admin/config/content/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 1'), 'fragment' => 'footnote-1'));
  $link_footnote_2 = l('2', 'admin/config/content/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 2'), 'fragment' => 'footnote-2'));
  $link_footnote_3 = l('3', 'admin/config/content/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 3'), 'fragment' => 'footnote-3'));
  $link_footnote_4 = l('4', 'admin/config/content/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 4'), 'fragment' => 'footnote-4'));
  $link_footnote_5 = l('5', 'admin/config/content/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 5'), 'fragment' => 'footnote-5'));
  $link_footnote_6 = l('6', 'admin/config/content/textsize', array('attributes' => array('title' =>  t('Footnote') . ' 6'), 'fragment' => 'footnote-6'));
  $form['textsize'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['textsize']['textsize_block_title'] = array(
    '#type' => 'radios',
    '#title' => t('Block title'),
    '#options' => array(
      'text_size' => t('Text Size'),
      'zoom' => t('Zoom'),
    ),
    '#default_value' => variable_get('textsize_block_title', 'text_size'),
    '#description' => t('Select the block title.') . ' ' . t('Default') . ': "' . t('Text Size') . '".',
  );
  $form['textsize']['textsize_block_type'] = array(
    '#type' => 'radios',
    '#title' => t('Block type'),
    '#options' => array(
      'text' => t('Text links') . ' [' . $link_footnote_1 . ']',
      'image' => t('Image links') . ' [' . $link_footnote_2 . ']',
      'select' => t('Select menu'),
    ),
    '#default_value' => variable_get('textsize_block_type', 'text'),
    '#description' => t('Select the type of block.') . ' ' . t('Default') . ': "' . t('Text links') . '".&#160;<br /><span id="footnote-1">[1] ' . t('Images are showed with !abbr_css.', array('!abbr_css' => $abbr_css)) . ' <span class="ts_ok">' . t('Ideal for Web Accessibility.') . '</span></span><br /><span id="footnote-2">[2] ' . t('Images in the !abbr_xhtml source code.', array('!abbr_xhtml' => $abbr_xhtml)) . ' <span class="warning">' . t('Warning') . ': ' . t('Not for: !abbr_wcag/!abbr_bitv 3.1! No hover action if !javascript is not activated!', array('!abbr_wcag' => $abbr_wcag, '!abbr_bitv' => $abbr_bitv, '!javascript' => '<em lang="en">JavaScript</em>')) . '</span></span>',
  );
  $form['textsize']['textsize_link_type'] = array(
    '#type' => 'radios',
    '#title' => t('Type of links'),
    '#options' => array(
      'variable' => t('Variable'),
      'fix' => t('Fixed') . ' [' . $link_footnote_3 . ']',
    ),
    '#default_value' => variable_get('textsize_link_type', 'variable'),
    '#description' => t('Select the type of links.') . ' ' . t('Default') . ': "' . t('Variable') . '".<br /><span id="footnote-3">[3] ' . t('Fixed links shows only 3 options for changing the text size (Increase, decrease and normal).') . '</span>',
  );
  $form['textsize_adv'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['textsize_adv']['textsize_element'] = array(
    '#type' => 'select',
    '#title' => t('!abbr_xhtml element', array('!abbr_xhtml' => $abbr_xhtml)),
    '#options' => array(
      'body' => 'body',
      'div' => 'div',
      'p' => 'p',
      'span' => 'span',
      'table' => 'table',
      'tr' => 'tr',
      'th' => 'th',
      'td' => 'td',
    ),
    '#default_value' => variable_get('textsize_element', 'body'),
    '#description' => t('Select the !abbr_xhtml element for the resize process.', array('!abbr_xhtml' => $abbr_xhtml)) . ' ' . t('Default') . ': "<em lang="en">body</em>". ' . t('The !body element is for the whole page.', array('!body' => '<em lang="en">body</em>')),
  );
  $form['textsize_adv']['textsize_element_class'] = array(
    '#type' => 'textfield',
    '#title' => t('!abbr_xhtml element !abbr_id/class', array('!abbr_xhtml' => $abbr_xhtml, '!abbr_id' => $abbr_id)),
    '#size' => 80,
    '#maxlength' => 80,
    '#default_value' => variable_get('textsize_element_class', ''),
    '#description' => t('Define one or more !abbr_id\'s ("#myid" or "#myid, div#myid-2") [!footnote_4] or one or more classes (".myclass" or ".myclass, div.myclass-2") for the !abbr_xhtml element.', array('!abbr_xhtml' => $abbr_xhtml, '!abbr_id' => $abbr_id, '!footnote_4' => $link_footnote_4)) . ' ' . t('Default') . ': ' . t('Empty, for the !body element.', array('!body' => '<em lang="en">body</em>')) . '<br/> <span id="footnote-4">[4]  <span class="warning">' . t('Warning') . ': ' . t('If you use !abbr_id\'s, uncheck: "!link_ts_important".', array('!abbr_id' => $abbr_id, '!link_ts_important' => $link_ts_important)) . '</span></span>',
  );
  $form['textsize_adv']['textsize_increment'] = array(
    '#type' => 'textfield',
    '#title' => t('Increases/decreases step'),
    '#default_value' => variable_get('textsize_increment', 6),
    '#size' => 2,
    '#maxlength' => 2,
    '#field_suffix' => '&#037;',
    '#required' => TRUE,
    '#description' => t("Percentage for the next increases or decreases step.") . ' ' . t('Default') . ': "6&#037;". ' . t('Allowed values') . ': 1-99&#037;',
  );
  $form['textsize_adv']['textsize_minimum'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum Text Size'),
    '#default_value' => variable_get('textsize_minimum', 50),
    '#size' => 3,
    '#maxlength' => 3,
    '#field_suffix' => '&#037;',
    '#required' => TRUE,
    '#description' => t('Default') . ': "50&#037;". ' . t('Allowed values') . ': 1-998&#037;',
  );
  $form['textsize_adv']['textsize_normal'] = array(
    '#type' => 'textfield',
    '#title' => t('Normal Text Size'),
    '#default_value' => variable_get('textsize_normal', 76),
    '#size' => 3,
    '#maxlength' => 3,
    '#field_suffix' => '&#037;',
    '#required' => TRUE,
    '#description' => t('Default') . ': "76&#037;". ' . t('Allowed values') . ': 2-999&#037;',
  );
  $form['textsize_adv']['textsize_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display normal text size as 100&#037;.'),
    '#default_value' => variable_get('textsize_display', 1),
    '#description' => t('Default') . ': ' . t('Checked.'),
  );
  $form['textsize_adv']['textsize_reset'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reset to normal size after maximum or minimum reached.'),
    '#default_value' => variable_get('textsize_reset', 0),
    '#description' => t('Default') . ': ' . t('Not checked.'),
  );
  $form['textsize_adv']['textsize_maximum'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Text Size'),
    '#default_value' => variable_get('textsize_maximum', 150),
    '#size' => 4,
    '#maxlength' => 4,
    '#field_suffix' => '&#037;',
    '#required' => TRUE,
    '#description' => t('Default') . ': "150&#037;". ' . t('Allowed values') . ': 3-1000&#037;',
  );
  $form['textsize_adv']['textsize_javascript'] = array(
    '#type' => 'checkbox',
    '#title' => t('Support !javascript', array('!javascript' => '<em lang="en">JavaScript</em>')),
    '#default_value' => variable_get('textsize_javascript', 1),
    '#description' => t('Support !javascript (!jquery) or only !abbr_php for caching mode: "Normal" and "Aggressive" and anonymous users.', array('!abbr_php' => $abbr_php, '!javascript' => '<em lang="en">JavaScript</em>', '!jquery' => '<em lang="en">jQuery</em>')) . ' ' . t('Default') . ': ' . t('Checked.'),
  );
  $form['textsize_adv']['textsize_important'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overwrite text size in templates') . ' [' . $link_footnote_5 . ']',
    '#default_value' => variable_get('textsize_important', 1),
    '#description' => t('Overwrite the font-size value of the current theme (with "!important"). Note: The !abbr_xhtml element for the resize process can not have the value "!important" in the !abbr_css style "font-size".', array('!abbr_xhtml' => $abbr_xhtml, '!abbr_css' => $abbr_css))  . ' ' . t('Default') . ': ' . t('Checked.') . ' <br/><span id="footnote-5">[5] ' . t('Not checked, for less code.') . ' <span class="warning">' . t('Warning') . ': ' . t('If you use the !abbr_xhtml element "body":',  array('!abbr_xhtml' => $abbr_xhtml)) . ' ' . t('Delete in your theme the !abbr_css style:', array('!abbr_css' => $abbr_css, '!abbr_id' => $abbr_id)) . ' "<code>body {font-size: ...;}</code>". ' . t('For example') . ': "<code><del>body {font-size: 12px;}</del></code>".</span></span>',
  );
  $form['textsize_adv']['textsize_message'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display message after changing text size'),
    '#default_value' => variable_get('textsize_message', 1),
    '#description' => t('Default') . ': ' . t('Checked.'),
  );
  $form['textsize_adv']['textsize_cookie_expires'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie Expires'),
    '#size' => 4,
    '#maxlength' => 4,
    '#field_suffix' => t('days'),
    '#default_value' => variable_get('textsize_cookie_expires', 365),
    '#description' => t('Default') . ': "365" ' . t('days') . ' . ' . t('Allowed values') . ': 1-3650 ' . t('days') . ' . ',
    '#required' => TRUE,
  );
  $form['textsize_adv']['textsize_cookie_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie Domain'),
    '#size' => 40,
    '#maxlength' => 100,
    '#field_prefix' => 'http://' . $_SERVER['SERVER_NAME'],
    '#default_value' => variable_get('textsize_cookie_domain', base_path()),
    '#description' => t('Default') . ': "' . base_path() . '". <span class="warning">' . t('Warning') . ': ' . t('After a change, the user must store the cookie again.') . '</span>',
    '#required' => TRUE,
  );
  $form['textsize_theme'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theme settings'),
    '#description' => t('Enable, disable or set the display of certain text size elements.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['textsize_theme']['textsize_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Toggle display'),
    '#description' => t('Enable or disable the display of certain text size elements.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['textsize_theme']['textsize_display']['textsize_display_subtitle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Subtitle'),
    '#default_value' => variable_get('textsize_display_subtitle', 0),
    '#description' => t('Ideal for image links and the select menue (title as label).') . ' ' . t('Default') . ': ' . t('Not checked.'),
  );
  $form['textsize_theme']['textsize_display']['textsize_display_increase'] = array(
    '#type' => 'checkbox',
    '#title' => t('Increase Text Size'),
    '#default_value' => variable_get('textsize_display_increase', 1),
    '#description' => t('Default') . ': ' . t('Checked.'),
  );
  $form['textsize_theme']['textsize_display']['textsize_display_decrease'] = array(
    '#type' => 'checkbox',
    '#title' => t('Decrease Text Size'),
    '#default_value' => variable_get('textsize_display_decrease', 1),
    '#description' => t('Default') . ': ' . t('Checked.'),
  );
  $form['textsize_theme']['textsize_display']['textsize_display_normal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Normal Text Size'),
    '#default_value' => variable_get('textsize_display_normal', 1),
    '#description' => t('Default') . ': ' . t('Checked.'),
  );
  $form['textsize_theme']['textsize_display']['textsize_display_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link text'),
    '#default_value' => variable_get('textsize_display_links', 1),
    '#description' => t('Default') . ': ' . t('Checked.') . ' <span class="warning">' . t('Warning') . ': ' . t('Not for block type "Image links" with images in the !abbr_xhtml source code.', array('!abbr_xhtml' => $abbr_xhtml)) . '</span>',
  );
  $form['textsize_theme']['textsize_display']['textsize_display_current_text_value'] = array(
    '#type' => 'radios',
    '#title' => t('Display current text size text and value'),
    '#options' => array(
      'text_value' => t('Text and value') . ' (' . t('for example') . ': "' . t("Current Size") . ': 100%")',
      'value' => t('Only the value') . ' (' . t('for example') . ': "<span title="' . t("Current Size") . ': 100%" class="textsize_current_help">100%</span>")',
      'hidden' => t('Hide text and value'),
      'remove' => t('Remove text and value in the source code') . ' [' . $link_footnote_6 . ']',
    ),
    '#default_value' => variable_get('textsize_display_current_text_value', 'text_value'),
    '#description' => t('Default') . ': "' . t('Text and value') . '". <br /><span id="footnote-6" class="warning">[6] ' . t('Warning') . ': ' . t('Not for screen readers or text browsers (text is not in the !abbr_xhtml source code).', array('!abbr_xhtml' => $abbr_xhtml)) . '</span>',
  );
  $form['textsize_theme']['textsize_inline'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display inline'),
    '#description' => t('Set the display of certain text size elements to inline or normal.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['textsize_theme']['textsize_inline']['textsize_display_list_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Subtitle, list and select menu'),
    '#default_value' => variable_get('textsize_display_list_inline', 0),
    '#description' => t('Default') . ': ' . t('Not checked.'),
  );
  $form['textsize_theme']['textsize_inline']['textsize_display_current_inline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Current text size'),
    '#default_value' => variable_get('textsize_display_current_inline', 0),
    '#description' => t('Default') . ': ' . t('Not checked.'),
  );
  return system_settings_form($form);
}

/**
 * Validate the textsize settings form.
 *
 * @see textsize_admin_settings()
 */
function textsize_admin_settings_validate($form, &$form_state) {
  $textsize_cookie_expires = textsize_cookie_expires($mode = 'php');
  $textsize_cookie_domain = variable_get('textsize_cookie_domain', base_path());
  $abbr_xhtml = '<abbr lang="en" xml:lang="en" title="Extensible Hypertext Markup Language">XHTML</abbr>';
  $abbr_css = '<abbr lang="en" xml:lang="en" title="' . t('Cascading Style Sheets') . '">CSS</abbr>';
  $abbr_id = '<abbr lang="en" xml:lang="en" title="Identification">ID</abbr>';
  $link_ts_important = l(t('Overwrite text size in templates'), 'admin/config/content/textsize', array('attributes' => array('title' => t('Overwrite text size in templates')), 'fragment' => 'edit-textsize-important'));
  $ts_el = $form_state['values']['textsize_element'];
  $ts_ec = filter_xss($form_state['values']['textsize_element_class']);
  $ts_in = $form_state['values']['textsize_increment'];
  $ts_no = $form_state['values']['textsize_normal'];
  $ts_di = $form_state['values']['textsize_display'];
  $ts_mi = $form_state['values']['textsize_minimum'];
  $ts_ma = $form_state['values']['textsize_maximum'];
  $ts_im = $form_state['values']['textsize_important'];
  $ts_co_ex = $form_state['values']['textsize_cookie_expires'];
  $ts_co_do = $form_state['values']['textsize_cookie_domain'];
  $ts_di_in = $form_state['values']['textsize_display_increase'];
  $ts_di_de = $form_state['values']['textsize_display_decrease'];
  $ts_di_no = $form_state['values']['textsize_display_normal'];
  $textsize_allowed_values = array();
  if (is_numeric($ts_in) && is_numeric($ts_no) && is_numeric($ts_mi) && is_numeric($ts_ma)) {
    if ($ts_in >= 1 && $ts_no >= 1 && $ts_mi >= 1 && $ts_ma >= 3) {
      $ts_st = ($ts_no - (round((($ts_no - $ts_mi) / $ts_in), 0) * $ts_in));
      $ts_en = ($ts_no + (round((($ts_ma - $ts_no) / $ts_in), 0) * $ts_in));
      for ($value = $ts_st; $value <= $ts_en; $value = $value + $ts_in ) {
        $textsize_allowed_values[] = $value;
      };
    }
  }
  if ((($ts_di_in + $ts_di_de + $ts_di_no) < 1) || ((($ts_di_in + $ts_di_de) == 0) && ($ts_di_no == 1))) {
    form_set_error('textsize_display_increase', t('Minimum 1 link "Increase Text Size" or "Decrease Text Size" is required.'));
  }
  if ($ts_el == "body") {
    if (!empty($ts_ec)) {
      form_set_error('textsize_element_class', t('The element class have to be empty for the !body element.', array('!body' => '<em lang="en">body</em>')));
    }
    elseif ($ts_im == 0) {
      drupal_set_message( t('Delete in your theme the !abbr_css style:', array('!abbr_xhtml' => $abbr_xhtml, '!abbr_css' => $abbr_css, '!abbr_id' => $abbr_id)) . ' "<code>body {font-size: ...;}</code>". ' . t('For example') . ': "<code><del>body {font-size: 12px;}</del></code>".</span>', "warning");
    }
  }
  if ($ts_el != "body") {
    if (empty($ts_ec)) {
      form_set_error('textsize_element_class', t('The !abbr_xhtml !abbr_id/element class can not be empty.', array('!abbr_xhtml' => $abbr_xhtml, '!abbr_id' => $abbr_id)) . ' ' . t('Textfield content') . ': "' . $ts_ec . '".');
    }
    elseif ($ts_ec{0} != "." && $ts_ec{0} != "#") {
     form_set_error('textsize_element_class', t('The !abbr_xhtml element !abbr_id/class have to be start with a hash ("#") for a !abbr_id or a point (".") for a class.', array('!abbr_xhtml' => $abbr_xhtml, '!abbr_id' => $abbr_id)));
    }
    elseif ($ts_ec == "." || $ts_ec == "#") {
      form_set_error('textsize_element_class', t('The !abbr_xhtml element !abbr_id/class can not have only a hash ("#") or a point (".").', array('!abbr_xhtml' => $abbr_xhtml, '!abbr_id' => $abbr_id)) . ' ' . t('Textfield content') . ': "' . $ts_ec . '".');
    }
    elseif (($ts_ec{0} == "#" && $ts_ec{1} == " ") || ($ts_ec{0} == "." && $ts_ec{1} == " ")) {
      form_set_error('textsize_element_class', t('The !abbr_xhtml element !abbr_id/class can not have a empty space (" ") after a hash ("#") or a point (".").',  array('!abbr_xhtml' => $abbr_xhtml, '!abbr_id' => $abbr_id)) . ' ' . t('Textfield content') . ': "' . $ts_ec . '".');
    }
  }
  // Text Size Increment
  if (!is_numeric($ts_in) || $ts_in != round($ts_in) || $ts_in{0} == "+") {
    form_set_error('textsize_increment', t('Please enter a integer in:') . ' "' . t('Increases/decreases step') . '".');
  }
  if ($ts_in < 1) {
    form_set_error('textsize_increment', t('The minimum step is 1&#037; in:') . ' "' . t('Increases/decreases step') . '".');
  }
  // Normal Text Size
  if (!is_numeric($ts_no) || $ts_no != round($ts_no) || $ts_no{0} == "+") {
    form_set_error('textsize_normal', t('Please enter a integer in:') . ' "' . t('Normal Text Size') . '".');
  }
  if (is_numeric($ts_no) && $ts_no == round($ts_no) && !in_array($_COOKIE['textsize'], $textsize_allowed_values)) {
    $_SESSION['textsize'] = $ts_no;
    setcookie("textsize", $ts_no, time()+$textsize_cookie_expires, $textsize_cookie_domain, "");
    drupal_set_message(t('The text size have been saved as %ts_value% (100&#037;).', array('%ts_value' => $ts_no)));
  }
  if ($ts_no > ($ts_ma - $ts_in)) {
    form_set_error('textsize_normal', t('The normal text size is bigger than the maximum normal size of: !ts_size%.', array('!ts_size' =>  ($ts_ma - $ts_in))));
  }
  if ($ts_no < ($ts_mi + $ts_in)) {
    form_set_error('textsize_normal', t('The normal text size is less than the minimum normal size of: !ts_size%.', array('!ts_size' =>  ($ts_mi + $ts_in))));
  }
  // Text Size Minimum
  if (!is_numeric($ts_mi) || $ts_mi != round($ts_mi) || $ts_mi{0} == "+") {
    form_set_error('textsize_minimum', t('Please enter a integer in:') . ' "' . t('Minimum Text Size') . '".');
  }
  if ($ts_mi >= $ts_no) {
    form_set_error('textsize_minimum', t('The minimum text size can not be the same or bigger value than the normal textsize.'));
  }
  if ($ts_mi < 1 || $ts_mi{0} == "-") {
    form_set_error('textsize_minimum', t('The minimum size is 1&#037; in:') . ' "' . t('Minimum Text Size') . '".');
  }
  // Text Size Maximum
  if (!is_numeric($ts_ma) || $ts_ma != round($ts_ma) || $ts_ma{0} == "+") {
    form_set_error('textsize_maximum', t('Please enter a integer in:') . ' "' . t('Maximum Text Size') . '".');
  }
  if ($ts_ma > 1000) {
    form_set_error('textsize_minimum', t('The maximum size is 1000&#037; in:') . ' "' . t('Maximum Text Size') . '".');
  }
  if ($ts_ma < 3 || $ts_ma{0} == "-") {
    form_set_error('textsize_minimum', t('The minimum size is 3&#037; in:') . ' "' . t('Minimum Text Size') . '".');
  }
  // Text Size Cookie Expires
  if (!is_numeric($ts_co_ex) || $ts_co_ex != round($ts_co_ex) || $ts_co_ex{0} == "+") {
    form_set_error('textsize_cookie_expires', t('Please enter a integer in:') . ' "' . t('Cookie Expires') . '".');
  }
  if ($ts_co_ex < 1 || $ts_co_ex{0} == "-") {
    form_set_error('textsize_cookie_expires', t('The minimum is 1 day in:') . ' "' . t('Cookie Expires') . '".');
  }
  if ($ts_co_ex > 3650) {
    form_set_error('textsize_cookie_expires', t('The maximum is 3650 day in:') . ' "' . t('Cookie Expires') . '".');
  }
  // Text Size Cookie Domain
  if (empty($ts_co_do{0})) {
    form_set_error('textsize_cookie_domain', t('The cookie domain can not have a empty space (" ") as first in:') . ' "' . t('Cookie Domain') . '".');
  }
  if (!empty($ts_co_do{0})) {
    if ($ts_co_do{0} != "/") {
      form_set_error('textsize_cookie_domain', t('Please enter a slash "/" as first in:') . ' "' . t('Cookie Domain') . '".');
    }
    elseif ($ts_co_do{0} == "/") {
      if (!empty($ts_co_do{1})) {
        if ($ts_co_do{1} == "/") {
          form_set_error('textsize_cookie_domain', t('Please enter only one slash "/" as first in:') . ' "' . t('Cookie Domain') . '".');
        }
        elseif ($ts_co_do{1} != "/") {
          if ($ts_co_do != base_path()) {
            drupal_set_message(t('Warning') . ': ' . t('The cookie domain: "!ts_co_do" is specific!', array('!ts_co_do' => $ts_co_do)), "warning");
          }
          elseif ($ts_co_do != variable_get('textsize_cookie_domain', base_path())) {
          drupal_set_message(t('Warning') . ': ' . t('The cookie domain has been changed.') . ' ' . t('After a change, the user must store the cookie again.'), "warning");
          }
        }
      }
    }
  }
  // Warning
  if ((!in_array("100", $textsize_allowed_values)) && $ts_di == 1) {
    drupal_set_message( t('This configuration generate not a normal text size of 100&#037; in the source code.'), "warning");
  }
  if ((!in_array("100", $textsize_allowed_values)) && $ts_di == 0) {
    drupal_set_message( t('Warning') . ': ' . t('This configuration generate and display not a normal text size of 100&#037;!'), "warning");
  }
}
