<?php

/**
 * @file
 * A Mail System with a fixed drupal_html_to_text() function.
 *
 * As will be in Drupal 7.5, see #1130198.
 */

class SubscriptionsMailSystem extends DefaultMailSystem implements MailSystemInterface {
  /**
   * Concatenate and wrap the e-mail body for plain-text mails.
   *
   * @param $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return
   *   The formatted $message.
   */
  public function format(array $message) {
    // Join the body array into one string.
    $message['body'] = implode("\n\n", $message['body']);
    // Convert any HTML to plain-text.
    $message['body'] = subscriptions_html_to_text($message['body']);
    // Wrap the mail body for sending.
    $message['body'] = drupal_wrap_mail($message['body']);
    return $message;
  }
}


/**
 * Transform an HTML string into plain text, preserving the structure of the
 * markup. Useful for preparing the body of a node to be sent by e-mail.
 *
 * The output will be suitable for use as 'format=flowed; delsp=yes' text
 * (RFC 3676) and can be passed directly to drupal_mail() for sending.
 *
 * We deliberately use LF rather than CRLF, see drupal_mail().
 *
 * This function provides suitable alternatives for the following tags:
 * <a> <em> <i> <strong> <b> <br> <p> <blockquote> <ul> <ol> <li> <dl> <dt>
 * <dd> <h1> <h2> <h3> <h4> <h5> <h6> <hr>
 *
 * @param $string
 *   The string to be transformed.
 * @param $allowed_tags (optional)
 *   If supplied, a list of tags that will be transformed. If omitted, all
 *   all supported tags are transformed.
 *
 * @return
 *   The transformed string.
 */
function subscriptions_html_to_text($string, $allowed_tags = NULL) {
  // Cache list of supported tags.
  static $supported_tags;
  if (empty($supported_tags)) {
    $supported_tags = array('a', 'em', 'i', 'strong', 'b', 'br', 'p', 'blockquote', 'ul', 'ol', 'li', 'dl', 'dt', 'dd', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'hr');
  }

  // Make sure only supported tags are kept.
  $allowed_tags = isset($allowed_tags) ? array_intersect($supported_tags, $allowed_tags) : $supported_tags;

  // Make sure tags, entities and attributes are well-formed and properly nested.
  $string = _filter_htmlcorrector(filter_xss($string, $allowed_tags));

  // Apply inline styles.
  $string = preg_replace('!</?(em|i)((?> +)[^>]*)?>!i', '/', $string);
  $string = preg_replace('!</?(strong|b)((?> +)[^>]*)?>!i', '*', $string);

  // Replace inline <a> tags with the text of link and a footnote.
  // 'See <a href="http://drupal.org">the Drupal site</a>' becomes
  // 'See the Drupal site [1]' with the URL included as a footnote.
  _drupal_html_to_mail_urls(NULL, TRUE);
  $pattern = '@(<a[^>]+?href="([^"]*)"[^>]*?>(.+?)</a>)@i';
  $string = preg_replace_callback($pattern, '_drupal_html_to_mail_urls', $string);
  $urls = _drupal_html_to_mail_urls();
  $footnotes = '';
  if (count($urls)) {
    $footnotes .= "\n";
    for ($i = 0, $max = count($urls); $i < $max; $i++) {
      $footnotes .= '[' . ($i + 1) . '] ' . $urls[$i] . "\n";
    }
  }

  // Split tags from text.
  $split = preg_split('/<([^>]+?)>/', $string, -1, PREG_SPLIT_DELIM_CAPTURE);
  // Note: PHP ensures the array consists of alternating delimiters and literals
  // and begins and ends with a literal (inserting $null as required).

  $tag = FALSE; // Odd/even counter (tag or no tag)
  $casing = NULL; // Case conversion function
  $output = '';
  $indent = array(); // All current indentation string chunks
  $lists = array(); // Array of counters for opened lists
  foreach ($split as $value) {
    $chunk = NULL; // Holds a string ready to be formatted and output.

    // Process HTML tags (but don't output any literally).
    if ($tag) {
      list($tagname) = explode(' ', strtolower($value), 2);
      switch ($tagname) {
        // List counters
        case 'ul':
          array_unshift($lists, '*');
          break;
        case 'ol':
          array_unshift($lists, 1);
          break;
        case '/ul':
        case '/ol':
          array_shift($lists);
          $chunk = ''; // Ensure blank new-line.
          break;

        // Quotation/list markers, non-fancy headers
        case 'blockquote':
          // Format=flowed indentation cannot be mixed with lists.
          $indent[] = count($lists) ? ' "' : '>';
          break;
        case 'li':
          $indent[] = isset($lists[0]) && is_numeric($lists[0]) ? ' ' . $lists[0]++ . ') ' : ' * ';
          break;
        case 'dd':
          $indent[] = '    ';
          break;
        case 'h3':
          $indent[] = '.... ';
          break;
        case 'h4':
          $indent[] = '.. ';
          break;
        case '/blockquote':
          if (count($lists)) {
            // Append closing quote for inline quotes (immediately).
            $output = rtrim($output, "> \n") . "\"\n";
            $chunk = ''; // Ensure blank new-line.
          }
          // Fall-through
        case '/li':
        case '/dd':
          array_pop($indent);
          break;
        case '/h3':
        case '/h4':
          array_pop($indent);
        case '/h5':
        case '/h6':
          $chunk = ''; // Ensure blank new-line.
          break;

        // Fancy headers
        case 'h1':
          $indent[] = '======== ';
          $casing = 'drupal_strtoupper';
          break;
        case 'h2':
          $indent[] = '-------- ';
          $casing = 'drupal_strtoupper';
          break;
        case '/h1':
        case '/h2':
          $casing = NULL;
          // Pad the line with dashes.
          $output = _drupal_html_to_text_pad($output, ($tagname == '/h1') ? '=' : '-', ' ');
          array_pop($indent);
          $chunk = ''; // Ensure blank new-line.
          break;

        // Horizontal rulers
        case 'hr':
          // Insert immediately.
          $output .= drupal_wrap_mail('', implode('', $indent)) . "\n";
          $output = _drupal_html_to_text_pad($output, '-');
          break;

        // Paragraphs and definition lists
        case '/p':
        case '/dl':
          $chunk = ''; // Ensure blank new-line.
          break;
      }
    }
    // Process blocks of text.
    else {
      // Convert inline HTML text to plain text; not removing line-breaks or
      // white-space, since that breaks newlines when sanitizing plain-text.
      $value = trim(decode_entities($value));
      if (drupal_strlen($value)) {
        $chunk = $value;
      }
    }

    // See if there is something waiting to be output.
    if (isset($chunk)) {
      // Apply any necessary case conversion.
      if (isset($casing)) {
        $chunk = $casing($chunk);
      }
      // Format it and apply the current indentation.
      $output .= drupal_wrap_mail($chunk, implode('', $indent)) . MAIL_LINE_ENDINGS;
      // Remove non-quotation markers from indentation.
      $indent = array_map('_drupal_html_to_text_clean', $indent);
    }

    $tag = !$tag;
  }

  return $output . $footnotes;
}

