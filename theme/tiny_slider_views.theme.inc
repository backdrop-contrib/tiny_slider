<?php

/**
 * @file
 * Theme.inc for functions.
 */

/**
 * Prepares variables for views carousel template.
 *
 * Default template: tiny-slider-views.tpl.php.
 *
 * @param array $vars
 *   An associative array containing:
 *   - view: A ViewExecutable object.
 *   - rows: The raw row data.
 */
function template_preprocess_tiny_slider_views(array &$vars) {
  $library_location = config_get('tiny_slider.settings', 'library');
  $handler = $vars['view']->style_plugin;

  // Sanitize settings before processing
  $settings = _tiny_slider_format_settings($handler->options);

  // Handle JSON configuration with security measures
  if (isValidJson($settings['configJson'])) {
    $config = json_decode($settings['configJson']);
    if ($config) {
      array_walk_recursive($config, function(&$value) {
        if (is_string($value)) {
          $value = check_plain($value);
        }
      });
      $vars['attributes']['data-settings'] = json_encode($config, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_QUOT | JSON_HEX_AMP);
    }
  }
  else {
    $vars['attributes']['data-settings'] = json_encode($settings, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_QUOT | JSON_HEX_AMP);
  }

  $vars['attributes']['class'][] = 'tiny-slider-wrapper';
  $vars['attributes']['class'][] = 'tiny-slider';

  // Add required libraries
  backdrop_add_library('system', 'jquery', TRUE);
  backdrop_add_library('system', 'jquery.once', TRUE);

  try {
    $attached = backdrop_add_library('tiny_slider', 'tinyslider.' . $library_location);
    render($attached);
  }
  catch (Exception $e) {
    watchdog_exception('tiny_slider', $e);
  }

  template_preprocess_views_view_unformatted($vars);
}
