<?php
// $Id: textsize-text.tpl.php,v 1.3 2010/05/21 17:16:49 christianzwahlen Exp $

/**
 * @file
 * Default theme implementation for rendering a block.
 *
 * Available variables:
 * - $dest: The drupal function drupal_get_destination().
 * - $block_title: Block title: "Text Size" or "Zoom".
 * - $list_inline: Display the ul list "inline" or not.
 * - $current_inline: Display the current text size "inline" or not.
 * - $subtitle: The subtitle.
 * - $subtitle_text: "Text Size"/"Zoom" or inline "Text Size: "/"Zoom: ".
 * - $textsize_normal: The text size normal link.
 * - $display_links: Show or hide ("display_hidden") the text in the links.
 * - $current_textsize: The current text size.
 * - $display_current_textsize: Show or hide ("display_hidden") the text of the current textsize.
 * - $display_current_textsize_text: Show or hide ("display_hidden").
 * - $link_type: Return "variable" for variable or fix.
 * - $increment: The increment step (default 5%).
 * - $normal: The textsize normal (default 75%).
 * - $current_textsize_text: The current textsize text "Current Size" or "Current Zoom".
 * - $textsize: The current text size (default 100%).
 *
 * @see template_preprocess_textsize_text()
 */
?>
<?php  if ($subtitle): ?>
<h3 class="<?php print $list_inline; ?>"><?php print $subtitle_text; ?></h3>
<?php endif; ?>
<ul class="textsize_<?php print $list_inline .' '. $current_inline; ?>">
<?php  if ($textsize_increase): ?>
  <li class="ts_increase_<?php print check_plain($link_type); ?>"><?php print l('<span class="'. $display_links .'">'. t('Increase') .'</span>', 'textsize/increase', array('attributes' => array('title' => $block_title .': '. t('Increase') .' +'. $increment .'%', 'class' => 'ts_icon ts_increase_'. $link_type .' textsize_increase text_'. $display_links), 'query' => $dest, 'html' => TRUE)); ?></li>
<?php endif; ?>
<?php  if ($textsize_decrease): ?>
  <li class="ts_decrease_<?php print check_plain($link_type); ?>"><?php print l('<span class="'. $display_links .'">'. t('Decrease') .'</span>', 'textsize/decrease', array('attributes' => array('title' => $block_title .': '. t('Decrease') .' -'. $increment .'%', 'class' => 'ts_icon ts_decrease_'. $link_type .' textsize_decrease text_'. $display_links), 'query' => $dest, 'html' => TRUE)); ?></li>
<?php endif; ?>
<?php  if ($textsize_normal): ?>
  <li class="ts_normal_<?php print check_plain($link_type); ?>"><?php print l('<span class="'. $display_links .'">'. t('Normal') .'</span>', 'textsize/normal', array('attributes' => array('title' => $block_title .': '. t('Normal') .' ='. $normal .'%', 'class' => 'ts_icon ts_normal_'. $link_type .' textsize_normal text_'. $display_links), 'query' => $dest, 'html' => TRUE)); ?></li>
<?php endif; ?>
</ul>
<?php  if ($current_textsize): ?>
<p class="textsize_current <?php print $current_inline .' '. $display_current_textsize .' current_text_'. $display_current_textsize_text .' text_'. $display_links; ?>"><span class="<?php print $display_current_textsize_text; ?>"><?php print $current_textsize_text; ?>: </span><span id="textsize_current" title="<?php print $current_textsize_text .': '. $textsize .'%'; ?>"><?php print $textsize; ?>%</span></p>
<?php endif; ?>
<div class="ts_clear"></div>