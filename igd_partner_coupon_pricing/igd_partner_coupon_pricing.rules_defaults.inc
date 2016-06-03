<?php
/**
 * @file
 * igd_partner_coupon_pricing.rules_defaults.inc
 * Add Coupon as per https://drupal.org/node/1898322
 */

/**
 * Implements hook_default_rules_configuration().
 */
function igd_partner_coupon_pricing_default_rules_configuration() {
  $items = array();
  $items['igd_partner_coupon_pricing'] = entity_import('rules_config', '{ "igd_partner_coupon_pricing" : {
      "LABEL" : "After Add to Cart",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Cart" ],
      "REQUIRES" : [
        "commerce_cart",
        "rules",
        "commerce_coupon",
        "rules_conditional",
        "rules_session_vars"
      ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "commerce_order_is_cart" : { "commerce_order" : [ "commerce_order" ] } },
        { "entity_has_field" : {
            "entity" : [ "site:current-cart-order" ],
            "field" : "commerce_coupon_order_reference"
          }
        }
      ],
      "DO" : [
        { "commerce_coupon_action_get_coupons_for_order" : {
            "USING" : { "commerce_order" : [ "commerce_order" ] },
            "PROVIDE" : { "order_coupons" : { "order_coupons" : "Coupons attached to this order" } }
          }
        },
        { "CONDITIONAL" : [
            {
              "IF" : { "data_is_empty" : { "data" : [ "order_coupons" ] } },
              "DO" : [
                { "CONDITIONAL" : [
                    {
                      "IF" : { "session_key_exists" : { "data_key" : "coupon" } },
                      "DO" : [
                        { "load_data_from_session" : {
                            "USING" : { "data_key" : "coupon" },
                            "PROVIDE" : { "loaded_session_data" : { "coupon_id" : "CouponId" } }
                          }
                        },
                        { "data_convert" : {
                            "USING" : { "type" : "integer", "value" : [ "coupon-id" ] },
                            "PROVIDE" : { "conversion_result" : { "coupon_int" : "Coupon Integer" } }
                          }
                        },
                        { "entity_fetch" : {
                            "USING" : { "type" : "commerce_coupon", "id" : [ "coupon-int" ] },
                            "PROVIDE" : { "entity_fetched" : { "commerce_coupon" : "Commerce Coupon" } }
                          }
                        },
                        { "CONDITIONAL" : [
                            {
                              "IF" : { "entity_has_field" : {
                                  "entity" : [ "commerce-coupon" ],
                                  "field" : "commerce_coupon_fixed_amount"
                                }
                              },
                              "DO" : [
                                { "list_add" : {
                                    "list" : [ "site:current-cart-order:commerce-coupon-order-reference" ],
                                    "item" : [ "commerce-coupon" ],
                                    "unique" : 1
                                  }
                                },
                                { "commerce_coupon_action_create_coupon_line_item" : {
                                    "USING" : {
                                      "commerce_coupon" : [ "commerce_coupon" ],
                                      "commerce_order" : [ "site:current-cart-order" ],
                                      "amount" : "0",
                                      "component_name" : [ "commerce-coupon:type:type" ],
                                      "currency_code" : [ "commerce-coupon:commerce-coupon-fixed-amount:currency-code" ]
                                    },
                                    "PROVIDE" : { "commerce_coupon_line_item" : { "commerce_coupon_line_item" : "commerce coupon line item" } }
                                  }
                                }
                              ]
                            }
                          ]
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        },
        { "redirect" : { "url" : "cart" } }
      ]
    }
  }');
  return $items;
}
