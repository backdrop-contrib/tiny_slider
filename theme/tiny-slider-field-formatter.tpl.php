<?php if ($attributes): ?>
<div data-settings='<?php print $attributes['data-settings']; ?>'
  <?php if (!empty($attributes['class'])) {
    print 'class="' . implode(' ', $attributes['class']) . '"';
  } ?>>
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
