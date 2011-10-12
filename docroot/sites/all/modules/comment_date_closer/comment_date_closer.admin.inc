<?php
/**
* @file
* Administration page callbacks for the comment_date_closer module.
*/

/**
* Form builder. Configure comment_date_closer.
*
* @ingroup forms
* @see system_settings_form().
*/

function comment_date_closer_admin_settings() {
  // Get an array of node types with internal names as keys and
  // "friendly names" as values. E.g.,
  // array('page' => Basic Page, 'article' => 'Articles')
  $types = node_type_get_types();
  foreach($types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }

  $form['comment_date_closer_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Comment thread will be autoclosed for the follwoing types'),
    '#options' => $options,
    '#default_value' => variable_get('comment_date_closer_node_types', array('page')),
    '#description' => t('A comment by date field will be available on these content types.'),
  );

  $form['#submit'][] = 'comment_date_closer_admin_settings_submit';
  return system_settings_form($form, TRUE);

}

function comment_date_closer_admin_settings_submit($form, $form_state) {
  // Loop through each of the content type checkboxes shown on the form.
  foreach ($form_state['values']['comment_date_closer_node_types'] as $key => $value) {
    // If the check box for a content type is unchecked, look to see whether
    // this content type has the comment_by field attached to it using the
    // field_info_instance function. If it does then we need to remove the
    // comment_by field as the administrator has unchecked the box.
    if (!$value) {
      $instance = field_info_instance('node', 'comment_by', $key);
      if (!empty($instance)) {
        field_delete_instance($instance, false);
        watchdog("comment_date_closer", 'Deleted comment_by field from content type:
          %key', array('%key' => $key));
      }
    } else {
      // If the check box for a content type  is checked, look to see whether
      // the field is associated with that content type. If not then add the
      // comment_by field to the content type.
      $instance = field_info_instance('node', 'comment_by', $key);
      if (empty($instance)) {
        $instance = array(
          'field_name' => 'comment_by',
	  'entity_type' => 'node',
	  'required' => 'true',
          'bundle' => $key,
          'label' => t('Comment By'),
	  'widget' => array(
		  'type' => 'date_popup',
	  ),
  );
 

	
      $instance = field_create_instance($instance);
      watchdog('comment_date_closer', 'Added comment_by field from content type: %key',
        array('%key' => $key));
      }
    }
  } // End foreach loop.
}
