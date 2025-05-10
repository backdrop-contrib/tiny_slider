<?php if (!empty($attributes)): ?>
  <div data-settings='<?php print check_plain($attributes['data-settings']); ?>'
    <?php if (!empty($attributes['class'])): ?>
      class="<?php print check_plain(implode(' ', $attributes['class'])); ?>"
    <?php endif; ?>>
    <?php print $output; ?>

    <?php if (!empty($settings['navAsThumbnails']) && $settings['navAsThumbnails'] == '1'): ?>
      <ul class="thumbs-slider"
          data-field-id="<?php print check_plain($settings['uniqueFieldID']); ?>">
        <?php print $thumbs; ?>
      </ul>
    <?php endif; ?>
  </div>
<?php endif; ?>
