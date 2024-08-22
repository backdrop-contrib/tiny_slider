<?php if ($attributes): ?>
<div data-settings='<?php print $attributes['data-settings']; ?>'
     class="tiny-slider-wrapper tiny-slider tns-slider tns-carousel tns-subpixel tns-calc tns-horizontal" >
  <?php endif; ?>
  <?php foreach ($rows as $row_count => $row): ?>
    <div <?php if (!empty($row_classes[$row_count])) {
      print 'class="' . implode(' ', $row_classes[$row_count]) . '"';
    } ?>>
      <?php print $row; ?>
    </div>
  <?php endforeach; ?>
  <?php if ($attributes): ?>
</div>
<?php endif; ?>
