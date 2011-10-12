<?php

/**
* @file
* Administration page callbacks for the private_comments module.
*/

/**
* Form builder. Configure private_comments.
*
* @ingroup forms
* @see system_settings_form().
*/

function private_comments_admin_settings() {
  // Get an array of node types with internal names as keys and
  // "friendly names" as values. E.g.,
  // array('page' => Basic Page, 'article' => 'Articles')
  $types = node_type_get_types();
  foreach($types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }

  $form['private_comments_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Comment thread will be autoclosed for the follwoing types'),
    '#options' => $options,
    '#default_value' => variable_get('private_comments_node_types', array('page')),
    '#description' => t('A comment by date field will be available on these content types.'),
  );

  $form['#submit'][] = 'private_comments_admin_settings_submit';
  return system_settings_form($form, TRUE);

}

function private_comments_admin_settings_submit($form, $form_state) {
  // Loop through each of the content type checkboxes shown on the form.
  foreach ($form_state['values']['private_comments_node_types'] as $key => $value) {
    // If the check box for a content type is unchecked, look to see whether
    // this content type has the comment_by field attached to it using the
    // field_info_instance function. If it does then we need to remove the
    // comment_by field as the administrator has unchecked the box.
    if (!$value) {
      $instance = field_info_instance('comment', 'is_public', "comment_node_$key");
      if (!empty($instance)) {
        field_delete_instance($instance, false);
        watchdog("private_comments", 'Deleted is_public comment field from content type:
          %key', array('%key' => $key));
      }
    } else {
      // If the check box for a content type  is checked, look to see whether
      // the field is associated with that content type. If not then add the
      // comment_by field to the content type.
      $instance = field_info_instance('comment', 'is_public', "comment_node_$key");
      if (empty($instance)) {
        $instance = array(
          'field_name' => 'is_public',
	  'entity_type' => 'comment',
	  'required' => 'true',
          'bundle' => "comment_node_$key",
          'label' => t('Is Public'),
	  'widget' => array(
		  'type' => 'options_buttons',
	  ),
	  'default_value' => array(array('value' => "0")),
  );
 

	
      $instance = field_create_instance($instance);
      watchdog('private_comments', 'Added is_public field from content type: %key',
        array('%key' => $key));
      }
    }
  } // End foreach loop.
}
