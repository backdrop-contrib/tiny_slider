<?php if ($attributes): ?>
<div data-settings='<?php print $attributes['data-settings']; ?>'
     class="tiny-slider-wrapper tiny-slider tns-slider tns-carousel tns-subpixel tns-calc tns-horizontal">
  <?php print $output; ?>
  <?php endif; ?>
  <?php if ($settings['navAsThumbnails'] == '1'): ?>
    <ul class="thumbs-slider"
        data-field-id="<?php print $settings['uniqueFieldID']; ?>">
      <?php print $thumbs; ?>
    </ul>
  <?php endif; ?>
  <?php if ($attributes): ?>
</div>
<?php endif; ?>
