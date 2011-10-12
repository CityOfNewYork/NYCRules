<?php

/**
 * @file
 * Subscriptions module mail gateway helper functions for upgrading mail_edit D5 to D6.
 */

/**
 * Implementation of hook_form_alter().
 *
 * Adds to the General Settings part at admin/settings/subscriptions.
 */
function _subscriptions_mail_form_mail_edit_list_form_alter(&$form, $form_state) {
  $form['subscriptions'] = array(
      '#type' => 'fieldset',
      '#title' => t('!Subscriptions module', array('!Subscriptions' => 'Subscriptions')),
      '#weight' => -5,
  );
  $form['subscriptions']['explain'] = array(
    '#markup'        => t('You have !Subscriptions mail templates that were created under Drupal 5. Please import or remove these templates.', array('!Subscriptions' => 'Subscriptions')),
  );
  $lang_query = "SELECT DISTINCT(language) FROM {mail_edit} ORDER BY language ASC";
  $lang_result = db_query($lang_query);
  $mail_langs = array();  //fetch all current translations
  while ($row = db_fetch_object($lang_result)) {
    $mail_langs[$row->language] = $row->language;
  }
  foreach (language_list() as $lang_key => $language) {
    $mail_langs[$lang_key] = $lang_key;
  }//<!-- fetch all current translations

  if (count($mail_langs) > 1) {
    $form['subscriptions']['languages'] = array(
      '#type'          => 'select',
      '#title'         => t('Language(s)'),
      '#default_value' => array(),
      '#options'       => $mail_langs,
      '#description'   => t('Select all the language(s) into which to import the Drupal 5 !Subscriptions mail templates.<br />Note: After successful importing, the old templates are removed automatically.', array('!Subscriptions' => 'Subscriptions')),
      '#multiple'      => TRUE,
    );
  }
  else {
    $form['subscriptions']['language'] = array(
      '#type'          => 'value',
      '#value'         => current($mail_langs),
    );
  }
  $form['subscriptions']['import'] = array(
    '#type'          => 'submit',
    '#value'         => t('Import'),
  );
  $form['subscriptions']['remove'] = array(
    '#type'          => 'submit',
    '#value'         => t('Remove'),
  );
  $form['#validate'][] = 'subscriptions_mail_mail_edit_list_form_validate';
  $form['#submit'][] = 'subscriptions_mail_mail_edit_list_form_submit';
}

function subscriptions_mail_mail_edit_list_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == $form_state['values']['import']) {
    if (!isset($form_state['values']['language']) && empty($form_state['values']['languages'])) {
      $form['subscriptions']['languages']['#error'] = TRUE;
      form_set_error('languages', t('Select at least one language to import into.'));
    }
  }
  return $form;
}

function subscriptions_mail_mail_edit_list_form_submit($form, &$form_state) {
  $languages = (isset($form_state['values']['language']) ? array($form_state['values']['language']) : $form_state['values']['languages']);

  switch ($form_state['values']['op']) {

    case $form_state['values']['remove']:
      if (db_table_exists('subscriptions_mail_edit')) {
        db_delete('subscriptions_mail_edit')
          ->execute();
      }
      if (db_table_exists('mail_edit_d5')) {
        db_delete('mail_edit_d5')
          ->condition('mailkey', 'subscriptions-%', 'LIKE')
          ->execute();
      }
      break;

    case $form_state['values']['import']:
      // Import digest records:
      $old_mailkey = 'subscriptions-digest';
      $new_mailkey = 'subscriptions_mail_digest';
      $result = db_query("SELECT * FROM {mail_edit_registry} WHERE id = :id", array(':id' => $new_mailkey));
      if ($registry = db_fetch_array($result)) {
        if (_subscriptions_mail_mail_edit_import($old_mailkey, $new_mailkey, $registry['description'], $languages)) {
          $digest_item = db_query("SELECT item_body FROM {subscriptions_mail_edit} WHERE mailkey = :mailkey", array(':mailkey' => $old_mailkey . '-item'))->fetchField();
          $digest_separator = db_query("SELECT item_body FROM {subscriptions_mail_edit} WHERE mailkey = :mailkey", array(':mailkey' => $old_mailkey . '-separator'))->fetchField();
          $digest_comment = db_query("SELECT item_body FROM {subscriptions_mail_edit} WHERE mailkey = :mailkey", array(':mailkey' => $old_mailkey . '-item-comment'))->fetchField();
          foreach ($languages as $language) {
            $id = db_insert('mail_edit')
              ->fields(array(
                'description' => '',
                'subject' => $digest_separator,
                'id' => $new_mailkey . '+item',
                'body' => $digest_item,
                'language' => $language,
              ))
              ->execute();
            $id = db_insert('mail_edit')
              ->fields(array(
                'description' => '',
                'subject' => '',
                'id' => $new_mailkey . '+comment',
                'body' => $digest_comment,
                'language' => $language,
              ))
              ->execute();
          }
          db_delete('subscriptions_mail_edit')
            ->condition('mailkey', $new_mailkey . '-%', 'LIKE')
            ->execute();
        }
      }

      // Import node/nid (+ comment) records:
      $result = db_query("SELECT * FROM {mail_edit_registry} WHERE id = :id", array(':id' => $new_mailkey));
      if ($registry = db_fetch_array($result)) {
        if (_subscriptions_mail_mail_edit_import('subscriptions-node-nid', 'subscriptions_content_node-nid', $registry['description'], $languages)) {
          $comment_item = db_query("SELECT item_body FROM {subscriptions_mail_edit} WHERE mailkey = :mailkey", array(':mailkey' => 'subscriptions-comment-item'))->fetchField();
          $comment_separator = db_query("SELECT item_body FROM {subscriptions_mail_edit} WHERE mailkey = :mailkey", array(':mailkey' => 'subscriptions-comment-separator'))->fetchField();
          foreach ($languages as $language) {
            $id = db_insert('mail_edit')
              ->fields(array(
                'description' => '',
                'subject' => $comment_separator,
                'id' => 'subscriptions_content_node-nid+comment',
                'body' => $comment_item,
                'language' => $language,
              ))
              ->execute();
          }
          db_delete('subscriptions_mail_edit')
            ->condition('mailkey', 'subscriptions-comment-%', 'LIKE')
            ->execute();
        }
      }

      // Import node/tid records:
      $result = db_query("SELECT * FROM {mail_edit_registry} WHERE id = :id", array(':id' => $new_mailkey));
      if ($registry = db_fetch_array($result)) {
        _subscriptions_mail_mail_edit_import('subscriptions-node-tid', 'subscriptions_taxonomy_node-tid', $registry['description'], $languages);
      }

      // Import node-type-* records:
      $old_mailkey = 'subscriptions-node-type-';
      $new_mailkey = 'subscriptions_content_node-type-';
      $result = db_select('mail_edit_registry', 'mer')
        ->fields('mer')
        ->condition('id', $new_mailkey . '%', 'LIKE')
        ->execute();
      foreach ($result as $registry) {
        $type = substr($registry->id, strlen($new_mailkey));
        _subscriptions_mail_mail_edit_import($old_mailkey . $type, $new_mailkey . $type, $registry->description, $languages);
      }
      break;
  }

  $dummy = array();
  if (db_table_exists('subscriptions_mail_edit') && db_query("SELECT COUNT(*) FROM {subscriptions_mail_edit}")->fetchField() === 0) {
    db_drop_table('subscriptions_mail_edit');
  }
  if (db_table_exists('mail_edit_d5') && db_query("SELECT COUNT(*) FROM {mail_edit_d5}")->fetchField() === 0) {
    db_drop_table('mail_edit_d5');
  }
}

function _subscriptions_mail_mail_edit_import($old_mailkey, $new_mailkey, $description, $languages) {
  $success = FALSE;
  if ($row = db_fetch_array(db_query("SELECT * FROM {mail_edit_d5} WHERE mailkey = :mailkey", array(':mailkey' => $old_mailkey)))) {
    if (empty($row['description'])) {
      $row['description'] = filter_xss($description, array());
    }
    $success = TRUE;
    foreach ($languages as $language) {
      $variables = array('%key' => $new_mailkey, '%language' => $language);
      if (db_query("SELECT COUNT(*) FROM {mail_edit} WHERE id = :id AND language = :language", array(':id' => $new_mailkey, ':language' => $language))->fetchField()) {
        drupal_set_message(t("%language translation of %key cannot be imported because it's already defined.", $variables), 'warning');
        $success = FALSE;
      }
      elseif (db_insert('mail_edit')
        ->fields(array(
          'description' => $row['description'],
          'subject' => $row['subject'],
          'id' => $new_mailkey,
          'body' => $row['body'],
          'language' => $language,
        ))
        ->execute()) {
        drupal_set_message(t('%language translation of %key has been imported.', $variables));
      }
      else {
        drupal_set_message(t('%language translation of %key failed to import.', $variables), 'error');
        $success = FALSE;
      }
    }
    if ($success) {
      db_delete('mail_edit_d5')
        ->condition('mailkey', $old_mailkey)
        ->execute();
    }
  }
  return $success;
}
