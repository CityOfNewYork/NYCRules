<?php
/**
 * @file
 * Contains the chart display plugin.
 *
 * @author Jimmy Berry ("boombatower", http://drupal.org/user/214218)
 */

/**
 * The plugin that handles the chart style.
 *
 * @ingroup views_style_plugins
 */
class chart_views_plugin_style_chart extends views_plugin_style {
  function option_definition () {
    $options = parent::option_definition();

    $options['type'] = array('default' => 'bhs');
    $options['width'] = array('default' => 600);
    $options['height'] = array('default' => 400);
    $options['label_append_value'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['type'] = array(
      '#type' => 'radios',
      '#title' => t('Type'),
      '#description' => t('Chart type, see <a href="http://code.google.com/apis/chart/">Google Chart API documentation</a>.'),
      '#options' => chart_types(),
      '#required' => TRUE,
      '#default_value' => $this->options['type'],
    );
    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#description' => t('Chart width in pixels'),
      '#size' => 8,
      '#required' => TRUE,
      '#default_value' => $this->options['width'],
    );
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#description' => t('Chart height in pixels'),
      '#size' => 8,
      '#required' => TRUE,
      '#default_value' => $this->options['height'],
    );
    $form['label_append_value'] = array(
      '#type' => 'checkbox',
      '#title' => t('Append value to label'),
      '#description' => t('If checked, calculated values will be appended in the chart legend.'),
      '#default_value' => $this->options['label_append_value'],
    );
  }

  function render() {
    $charts = array();
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);
    $set = 0;
    foreach ($sets as $title => $records) {
      $chart = array(
        '#theme' => 'chart',
        '#chart_id' => drupal_clean_css_identifier($this->view->name . '-' . $this->display->id . '-' . $set++),
        '#type' => $this->options['type'],
        '#title' => $title, // If the set has a title then set the chart title.
        '#size' => array(
          '#width' => $this->options['width'],
          '#height' => $this->options['height'],
        ),
        '#data' => array(),
        '#labels' => array(),
        '#data_colors' => array(),
      );

      foreach ($records as $row_index => $row) {
        // @TODO Possibly handle data grouping by row?
        foreach ($this->view->field as $key => $field) {
          $chart['#data'][] = $row->$key;
          $chart['#labels'][] = $field->options['label'] . ($this->options['label_append_value'] ? ': ' . $row->$key : ''); // @TODO Provide a way to change format.
          $chart['#data_colors'][] = chart_unique_color($key);
        }
      }

      // Since view expects string output we can't save render array for later.
      $charts[$chart['#chart_id']] = drupal_render($chart);
    }

    return implode($charts);
  }
}
