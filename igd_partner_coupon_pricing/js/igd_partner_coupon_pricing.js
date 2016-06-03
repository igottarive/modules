(function($) {
  /**
   * Add an extra function to the Drupal ajax object which allows us to trigger
   * an ajax response without an element that triggers it.
   */
  Drupal.ajax.prototype.partnerModal = function() {
    var ajax = this;

    // Do not perform another ajax command if one is already in progress.
    if (ajax.ajaxing) {
      return false;
    }

    try {
      jQuery.ajax(ajax.options);
    } catch (err) {
      return false;
    }

    return false;
  };

  //The product and coupon pricing logic
  Drupal.behaviors.igd_partner_coupon_pricing_array = {
    attach : function(context, settings) {
      prices = settings.igd_partner_coupon_pricing;
      updatePricing(prices);
    }
  };

  //The popup logic for a partner hash
  Drupal.behaviors.igd_partner_coupon_pricing_popup = {
    attach : function(context, settings) {
      //If there's a hash, update the partner link & call popup
      vars = getHashVariables(location.hash);

      //Define a custom ajax action not associated with an element.
      var selector = 'a.ctools-modal-igd_partner_coupon_pricing-style';
      var block = 'div.block-igd-partner-coupon-pricing';
      //a_aid = postaffiliate pro variable for affiliate ID

      var aHref = $(selector).attr('href') + vars.a_aid + '?state=' + location.pathname.replace('/','');

      if(vars.a_aid && jQuery(selector).length) {
        //Update href
        $(selector).once(function () {
          this.href = aHref;
        });
      } else if($(selector).length) {
        //The state page without a partner anchor due to the block
        $(selector).once(function () {
          aHref = $(selector).attr('href') + 'noexist';
          this.href = aHref;
        });
      } else {
        //Not the state page due to the block
        //Fallthrough
      }
      jQuery(document).ready(function() {
        if (typeof Drupal.ajax[aHref] !== 'undefined') {
          Drupal.ajax[aHref].partnerModal();
          Drupal.ajax[aHref].success = (function(response, status){
            prices = settings.igd_partner_coupon_pricing;
            updatePricing(prices);
            Drupal.ajax.prototype.success.call(this, response, status);

            if(typeof settings.igd_partner_coupon_pricing !== 'undefined' && 
              settings.igd_partner_coupon_pricing.popup == "0") {
                Drupal.CTools.Modal.dismiss();
            }
          });
        }

        //Get partner pricing info
        prices = settings.igd_partner_coupon_pricing;
        updatePricing(prices);

        //Dismiss popup
        jQuery('#modalBackdrop, #modalContent').click(function() {
          Drupal.CTools.Modal.dismiss();
        });

        //Remove empty class so block shows if popup is not empty
        if(typeof settings.igd_partner_coupon_pricing !== 'undefined' && 
          settings.igd_partner_coupon_pricing.popup != "0") {
            $(block).removeClass('empty');
        }
      });
    }
  }
})(jQuery);

function getHashVariables(hash) {
  var data   = new Object();
  var pairs = hash.substring(hash.indexOf('#')+1).split('&');
  for(var key in pairs) {
    var value = pairs[key].split("=");
    data[value[0]] = value[1];
  }
  return data;
} 

function updatePricing(prices) {
  if( typeof prices === 'undefined') return;
  //Get retail price for the sku
  retail = jQuery('.igd-retail-price');
  retail.text('$' + prices.products[retail.attr('sku')]);

  coupons = prices.coupons;
  //returns "first" property
  if (typeof coupons === 'object') {
    jQuery.each(coupons, function(element,coup) {
      coupPrice = coup.toFixed(2);
    });
  } else {
    coupPrice = 0;
  }

  //Set coupon price or 0
  jQuery('.igd-coupon-price').text('$' + coupPrice);

  //Set to retail - coupon price or 0
  jQuery('.igd-final-price').each(function(index) {
    sku = jQuery(this).attr('sku');
    diff = prices.products[sku] - coupPrice;
    if(diff < 0) diff = 0;
    jQuery(this).text('$' + diff.toFixed(2));
  });
}
