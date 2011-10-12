<?php

/**
 * @file
 * Views support.
 */

/**
 * Implements hook_views_data_alter().
 */
function relation_views_data_alter(&$data) {
  // Find out which entity type has which base table.
  $entity_infos = entity_get_info();
  $entity_tables = array();
  foreach ($entity_infos as $entity_type => $entity_info) {
    if (isset($entity_info['base table'])) {
      $entity_tables[$entity_type] = $entity_info['base table'];
    }
  }
  $field = field_info_field('endpoints');
  $relation_data_table_name = _field_sql_storage_tablename($field);
  $entity_id_field_name = _field_sql_storage_columnname('endpoints', 'entity_id');
  $entity_type_field_name = _field_sql_storage_columnname('endpoints', 'entity_type');
  // Build the relations between the different tables.
  $types = relation_get_types();
  foreach ($types as $type => $relation_type) {
    if ($relation_type->max_arity != 2) {
      continue;
    }
    $target_index = $relation_type->directional ? 'target_bundles' : 'source_bundles';
    foreach ($relation_type->source_bundles as $source_bundle) {
      $source_bundle = explode(':', $source_bundle, 2);
      $entity_type_left = $source_bundle[0];
      $relationship_field = $entity_infos[$entity_type_left]['entity keys']['id'];
      $base_table_left = $entity_tables[$entity_type_left];
      $t_arguments = array(
        '@left' => $entity_type_left,
        '@relation_type_label' => $relation_type->label,
      );
      foreach ($relation_type->$target_index as $target_bundle) {
        $target_bundle = explode(':', $target_bundle, 2);
        $entity_type_right = $target_bundle[0];
        $base_table_right = $entity_tables[$entity_type_right];
        $t_arguments['@right'] = $entity_type_right;
        $data[$base_table_left]['relation_' . $type . '_' . $entity_type_right] = array(
          'title' => t('Relation: @relation_type_label (@left <-> @right)', $t_arguments),
          'help' => t('Provides a relationship from @left to @right via the relation @relation_type_label', $t_arguments),
          'relationship' => array(
            // relation_handler_relationship::options_form() relies on this check_plain().
            'label' => check_plain($relation_type->label),
            'base' => $base_table_right,
            'base field' => $entity_infos[$entity_type_right]['entity keys']['id'],
            'relationship field' => $relationship_field,
            'handler' => 'relation_handler_relationship',
            'relation_type' => $type,
            'entity_type_left' => $entity_type_left,
            'entity_type_right' => $entity_type_right,
            'directional' => $relation_type->directional,
            'join_handler' => 'relation_handler_join',
          ),
        );
      }
    }
  }
}
