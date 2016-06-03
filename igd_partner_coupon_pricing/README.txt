Make sure adding coupon to cart rule works correctly

Steps to enable:
1) Enable Module
2) Add block to the page you want it on (Context /admin/structure/context/list/state-page/edit)
3) Add class "empty" to the block /admin/structure/block/manage/igd_partner_coupon_pricing/igd_partner_coupon_pricing_block/configure
4) Goto /california-drivers-ed/#a_aid=swerveca to see it work
4b) https://igottadrive.com/partnerid/MttamDS/#a_aid=MttamDS
Last) Add content on the page in the form of 
  <div class="igd-retail-price" sku="HTRCACourse">Retail</div>
  <div class="igd-coupon-price" sku="HTRCACourse">Coupon</div>
  <div class="igd-final-price" sku="HTRCACourse">Final</div>
