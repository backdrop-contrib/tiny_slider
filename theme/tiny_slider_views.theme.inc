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

  $settings = _tiny_slider_format_settings($handler->options);

  if (isValidJson($settings['configJson'])) {
    $config = json_decode($settings['configJson']);
    $vars['attributes']['data-settings'] = json_encode($config, JSON_FORCE_OBJECT);
  }
  else {
    $vars['attributes']['data-settings'] = json_encode($settings, JSON_FORCE_OBJECT);
  }
  $vars['attributes']['class'][] = 'tiny-slider-wrapper';
  $vars['attributes']['class'][] = 'tiny-slider';

  backdrop_add_library('system', 'jquery', TRUE);
  backdrop_add_library('system', 'jquery.once', TRUE);
  $attached = backdrop_add_library('tiny_slider', 'tinyslider.' . $library_location);

  render($attached);
  template_preprocess_views_view_unformatted($vars);
}

