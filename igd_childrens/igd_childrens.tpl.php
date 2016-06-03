<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block info-block block-<?php print $block->module ?>">

<?php if ($block->subject): ?>
  <h2><?php print $block->subject ?></h2>
<?php endif;?>

  <div class="content">
    <div class="donation-meter">
      <strong>Our Goal</strong>
      <strong class="goal">$<?php print $goal; ?></strong>
      <span class="glass">
        <strong class="total" style="bottom: <?php print $percent; ?>%">$<?php print $total; ?></strong>
        <span class="amount" style="height: <?php print $percent; ?>%"></span>
      </span>
      <div class="bulb">
        <span class="red-circle"></span>
        <span class="filler">
          <span></span>
        </span>
      </div>
    </div>
  </div>
  <p>We've had <?php print $count; ?> people make this happen. Join us and make a difference.</p>
</div>
