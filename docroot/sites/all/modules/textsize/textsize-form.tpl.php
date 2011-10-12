<?php
// $Id: textsize-form.tpl.php,v 1.2 2009/11/17 23:27:42 christianzwahlen Exp $

/**
 * @file
 * Form theme implementation for rendering a block.
 *
 * Available variables:
 * - $list_inline: Display the ul list "inline" or not.
 * - $current_inline: Display the current text size "inline" or not.
 * - $current_textsize: The current text size.
 * - $display_current_textsize: Show or hide ("display_hidden") the text of the current textsize.
 * - $display_current_textsize_text: Show or hide ("display_hidden").
 * - $textsize_form: The form.
 * - $current_textsize_text: The current textsize text "Current Size" or "Current Zoom".
 * - $textsize: The current text size (default 100%).
 *
 * @see template_preprocess_textsize_form()
 */
?>
<div id="textsize" class="textsize_<?php print $list_inline .' '. $current_inline; ?> container-inline">
  <?php print $textsize_form; ?>
  <?php  if ($current_textsize): ?>
  <p class="textsize_current <?php print $current_inline .' '. $display_current_textsize .' current_text_'. $display_current_textsize_text .' text_display'; ?>"><span class="<?php print $display_current_textsize_text; ?>"><?php print $current_textsize_text; ?>: </span><span id="textsize_current" title="<?php print $current_textsize_text .': '. $textsize .'%'; ?>"><?php print $textsize; ?>%</span></p>
  <?php endif; ?>
</div>
<div class="ts_clear"></div>