<?php

/**
 * Implements hook_rules_action_info().
 */
function igd_commerce_shipping_rules_action_info() {

  $actions = array();
  $actions['commerce_shipping_service_variables'] = array(
    'label' => t('Get Commerce Shipping Service Variables'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'unknown',
        'label' => t('Commerce Shipping Lineitem'),
      ),
    ),
    'provides' => array(
      'wait_days' => array(
        'type' => 'duration',
        'label' => 'Wait Days'
      ),
      'delivery_days' => array(
        'type' => 'duration',
        'label' => 'Delivery Days'
      ),
      'usps_type' => array(
        'type' => 'text',
        'label' => 'Usps Type'
      ),
      'mailing_days' => array(
        'type' => 'text',
        'label' => 'Mailing Days'
      ),
    ),
    'group' => t('Commerce Shipping'),
    'base' => 'commerce_shipping_service_igd_get_variables',
  );

  return $actions;
}

/*
 * Split out the data from the array of shipping options
*/
function commerce_shipping_service_igd_get_variables($field) {
  $services = igd_commerce_shipping_commerce_shipping_service_info();
  $ship = $field->data['shipping_service']['name'];
  if(empty($services[$ship])) return;
  return array(
    'wait_days' => $services[$ship]['wait_days'],
    'delivery_days' => $services[$ship]['delivery_days'],
    'usps_type' => $services[$ship]['usps_type'],
    'mailing_days' => $services[$ship]['mailing_days'],
  );
}
