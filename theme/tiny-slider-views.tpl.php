<?php if (!empty($attributes)): ?>
  <div data-settings='<?php print check_plain($attributes['data-settings']); ?>'
    <?php if (!empty($attributes['class'])): ?>
      class="<?php print check_plain(implode(' ', $attributes['class'])); ?>"
    <?php endif; ?>>

    <?php foreach ($rows as $row_count => $row): ?>
      <div <?php if (!empty($row_classes[$row_count])): ?>
        class="<?php print check_plain(implode(' ', $row_classes[$row_count])); ?>"
      <?php endif; ?>>
        <?php print $row; ?>
      </div>
    <?php endforeach; ?>
  </div>
<?php endif; ?>
