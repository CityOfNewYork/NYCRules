<?php

/**
 * @file
 * Administrative functions for Relation module.
 */

/**
 * List all relation_types (page callback).
 */
function relation_type_list() {
  $relation = relation_entity_info();
  $field_ui = module_exists('field_ui');
  $headers = array(
    array('data' => t('Name'), 'width' => '40%'),
    array('data' => t('Operations'), 'colspan' => $field_ui ? '4' : '2'));
  $rows = array();
  foreach ($relation['relation']['bundles'] as $type => $relation_type) {
    $url = 'admin/structure/relation/manage/' . $type;
    $row = array(l($type, $url));
    $row[] = l(t('edit'), $url . '/edit');
    if ($field_ui) {
      $row[] =  l(t('manage fields'), $url . '/fields');
      $row[] =  l(t('display fields'), $url . '/display');
    }
    $row[] =  l(t('delete'), $url . '/delete');
    $rows[] = $row;
  }
  $output = array(
    '#theme' => 'table',
    '#header' => $headers,
    '#rows' => $rows,
  );
  return $output;
}

/**
 * Relation relation type bundle settings form.
 *
 * @param $relation_type
 *   Relation type machine name. If this is not provided, assume that we're
 *   creating a new relation type.
 */
function relation_type_form($form, &$form_state, $relation_type = array(), $op = 'edit') {
  $form['#write_record_keys'] = array();
  if ($relation_type) {
    $relation_type = (object) $relation_type;
    if ($relation_type) {
      $form['#write_record_keys'][] = 'relation_type';
    }
  }
  else {
    $relation_type = (object) array(
      'relation_type' => '',
      'label' => '',
      'reverse_label' => '',
      'bundles' => array(),
      'directional' => FALSE,
      'transitive' => FALSE,
      'r_unique' => FALSE,
      'min_arity' => 2,
      'max_arity' => 2,
      'source_bundles' => array(),
      'target_bundles' => array(),
    );
  }
  $form['name'] = array( // use 'name' for /misc/machine-name.js
    '#type'          => 'textfield',
    '#title'         => t('Label'),
    '#description'   => t('Display name of the relation type. This is also used as the predicate in natural language formatters (ie. if A is related to B, you get "A [label] B")'),
    '#default_value' => $relation_type->label,
    '#required'      => TRUE,
  );
  $form['relation_type'] = array(
    '#type'          => 'machine_name',
    '#default_value' => $relation_type->relation_type,
    '#maxlength' => 32,
    '#disabled'      => $relation_type->relation_type,
    '#machine_name' => array(
      'exists' => 'relation_type_load',
    ),
  );
  $form['directional'] = array(
    '#type'           => 'checkbox',
    '#title'          => 'Directional',
    '#description'   => t('A directional relation is one that does not imply the reverse relation. For example, a "likes" relation is directional (A likes B does not neccesarily mean B likes A), whereas a "similar to" relation is non-directional (A similar to B implies B similar to A. Non-directional relations are also known as symmetric relations.'),
    '#default_value'  => $relation_type->directional,
  );
  $form['reverse_label'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Reverse label'),
    '#description'   => t('Reverse label of the relation type. This is used as the predicate by formatters of directional relations, when you need to display the reverse direction (ie. from the target entity to the source entity). If this is not supplied, the forward label is used.'),
    '#default_value' => $relation_type->reverse_label,
    '#states' => array(
      'visible' => array(   // action to take.
        ':input[name="directional"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['transitive'] = array(
    '#type'           => 'checkbox',
    '#title'          => 'Transitive',
    '#description'   => t('A transitive relation implies that the relation passes through intermediate entities (ie. A=>B and B=>C implies that A=>C). For example "Ancestor" is transitive: your ancestor\'s ancestor is also your ancestor. But a "Parent" relation is non-transitive: your parent\'s parent is not your parent, but your grand-parent.'),
    '#default_value'  => $relation_type->transitive,
  );
  $form['r_unique'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Unique'),
    '#description'    => t('Whether relations of this type are unique (ie. they can not contain exactly the same end points as other relations of this type).'),
    '#default_value'  => $relation_type->r_unique,
  );
  // these should probably be changed to numerical (validated) textfields.
  $options = array('2' => '2', '3' => '3', '4' => '4', '5' => '5', '8' => '8');
  $form['min_arity'] = array(
    '#type' => 'select',
    '#title' => t('Minimum Arity'),
    '#options' => $options,
    '#description' => t('Minimum number of entities joined by relations of this type (e.g. three siblings in one relation). <em>In nearly all cases you will want to leave this set to 2</em>.'),
    '#default_value' => $relation_type->min_arity ? $relation_type->min_arity : 2,
    '#states' => array(
      'disabled' => array(   // action to take.
        ':input[name="directional"]' => array('checked' => TRUE),
      ),
    ),
  );

  $options = array('2' => '2', '3' => '3', '4' => '4', '5' => '5', '8' => '8', '0' => t('Infinite'));
  $form['max_arity'] = array(
    '#type' => 'select',
    '#title' => t('Maximum Arity'),
    '#options' => $options,
    '#description' => t('Maximum number of entities joined by relations of this type. <em>In nearly all cases you will want to leave this set to 2</em>.'),
    '#default_value' => isset($relation_type->max_arity) ? $relation_type->max_arity : 2,
    '#states' => array(
      'disabled' => array(   // action to take.
        ':input[name="directional"]' => array('checked' => TRUE),
      ),
    ),
  );
  $counter = 0;
  foreach (entity_get_info() as $entity_type => $entity) {
    $bundles[$entity['label']]["$entity_type:*"] = 'all ' . $entity['label'] . ' bundles';
    $counter += 2;
    if (isset($entity['bundles'])) {
      foreach ($entity['bundles'] as $bundle_id => $bundle) {
        $bundles[$entity['label']]["$entity_type:$bundle_id"] = $bundle['label'];
        $counter++;
      }
    }
  }
  $form['source_bundles'] = array(
    '#type'          => 'select',
    '#title'         => 'Available source bundles',
    '#options'       => $bundles,
    '#size'          => max(12, $counter),
    '#default_value' => $relation_type->source_bundles,
    '#multiple'      => TRUE,
    '#description'   => 'Bundles that are not selected will not be available as sources for directional, or end points of non-directional relations relations. Ctrl+click to select multiple. Note that selecting all bundles also include bundles not yet created for that entity type.',
  );
  $form['target_bundles'] = array(
    '#type'          => 'select',
    '#title'         => 'Available target bundles',
    '#options'       => $bundles,
    '#size'          => max(12, $counter),
    '#default_value' => $relation_type->target_bundles,
    '#multiple'      => TRUE,
    '#description'   => 'Bundles that are not selected will not be available as targets for directional relations. Ctrl+click to select multiple.',
    '#states' => array(
      '!visible' => array(   // action to take.
        ':input[name="directional"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  return $form;
}

/**
 * Submit data from bundle settings page.
 */
function relation_type_form_submit($form, &$form_state) {
  $relation_type = $form_state['values']['relation_type'];
  $min_arity = $form_state['values']['directional'] ? 2 : $form_state['values']['min_arity'];
  $max_arity = $form_state['values']['directional'] ? 2 : $form_state['values']['max_arity'];
  $record = array(
    'relation_type'   => $relation_type,
    'min_arity'   => $min_arity,
    'max_arity'   => $max_arity,
    'label' => $form_state['values']['name'],
    'reverse_label' => $form_state['values']['reverse_label'],
    'directional' => $form_state['values']['directional'],
    'transitive' => $form_state['values']['transitive'],
    'r_unique' => $form_state['values']['r_unique'],
    'source_bundles' => $form_state['values']['source_bundles'],
    'target_bundles' => $form_state['values']['target_bundles'],
  );
  relation_type_save($record, $form['#write_record_keys']);
  $form_state['redirect'] = "admin/structure/relation/edit/$relation_type";

  drupal_set_message(t('The %relation_type relation type has been saved.', array('%relation_type' => $relation_type)));
}

/**
 * Menu callback; deletes a single relation type.
 */
function relation_type_delete_confirm($form, &$form_state, $relation_type) {
  $form['relation_type'] = array('#type' => 'value', '#value' => $relation_type->relation_type);
  $form['label'] = array('#type' => 'value', '#value' => $relation_type->label);

  $message = t('Are you sure you want to delete the %label relation type?', array('%label' => $relation_type->label));
  $caption = '';

  $num_relations = relation_query()
    ->propertyCondition('relation_type', $relation_type->relation_type)
    ->count()
    ->execute();
  if ($num_relations) {
    $caption .= '<p>' . format_plural($num_relations,
      'The %label relation type is used by 1 relation on your site. If you remove this relation type, you will not be able to edit  %label relations and they may not display correctly.',
      'The %label relation type is used by @count relations on your site. If you remove %label, you will not be able to edit %label relations and they may not display correctly.',
      array('%label' => $relation_type->label, '@count' => $num_relations)) . '</p>';
  }

  $caption .= '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $message, 'admin/structure/relation', $caption, t('Delete'));
}

/**
 * Process relation type delete confirm submissions.
 */
function relation_type_delete_confirm_submit($form, &$form_state) {
  relation_type_delete($form_state['values']['relation_type']);

  $t_args = array('%label' => $form_state['values']['label']);
  drupal_set_message(t('The %label relation type has been deleted.', $t_args));
  watchdog('relation', 'Deleted the %label relation type.', $t_args, WATCHDOG_NOTICE);

  // TODO: relation_types_rebuild() ?;
  menu_rebuild();

  $form_state['redirect'] = 'admin/structure/relation';
  return;
}

/**
 * Generate relations
 */
function relation_generate_form($form, &$form_state) {
  $types = relation_get_types();
  foreach( $types as $id => $type) {
    $types[$id] = $type->label;
  }

  $form['relation_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Relation types'),
    '#description' => t('Select relation types to create relations from. If no types are selected, relations will be generated for all types.'),
    '#options' => $types,
  );
  $form['relation_number'] = array(
    '#type' => 'textfield',
    '#title' => t('How many relations would you like to generate of each type?'),
    '#default_value' => 10,
    '#size' => 10,
  );
  $form['relation_kill'] = array(
    '#type' => 'checkbox',
    '#title' => t('Kill all existing relations first.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
  );
  return $form;
}

function relation_generate_form_submit($form, &$form_state) {
  $number = $form_state['values']['relation_number'];
  $types = $form_state['values']['relation_types'];
  $kill = $form_state['values']['relation_kill'];
  if (is_numeric($number) && $number>0) {
    $types = array_keys(array_filter($types));
    $rids = relation_generate_relations($number, $types, $kill);
    drupal_set_message(t("Generated %count relations (rids from %first to %last).", array('%count' => count($rids),'%first' => $rids[0],'%last' => end($rids))));
  }
}
