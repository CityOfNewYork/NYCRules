
AUTHORS
-------

 * Tj Holowaychuk <http://www.350designs.com/>
 * Jimmy Berry ("boombatower", http://drupal.org/user/214218)

DOCUMENATION
------------

 * http://code.google.com/p/drupal-chart-api/w/list
 * chart_build() in chart.module
 * chart.api.php

EXAMPLE
-------

$chart = array(
  '#chart_id' => 'test_chart',
  '#title' => t('Servings'),
  '#type' => CHART_TYPE_PIE_3D,
);

$chart['#data']['fruits'] = 3;
$chart['#data']['meats']  = 2;
$chart['#data']['dairy']  = 5;

echo theme('chart', array('chart' => $chart));
