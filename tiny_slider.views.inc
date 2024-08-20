<?php
/**
 * @file
 * Defines the View Style Plugins for Views TinySlider module.
 */

/**
 * Implements hook_views_plugins().
 */
function tiny_slider_views_plugins() {
  return [
    'style' => [
      'tinyslider' => [
        'title' => t('TinySlider'),
        'help' => t('Display the results in a Tiny Slider.'),
        'handler' => 'tiny_slider_plugin_style_tinyslider',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => TRUE,
        'uses fields' => TRUE,
        'uses row class' => TRUE,
        'type' => 'normal',
        'path' => backdrop_get_path('module', 'tiny_slider'),
        'theme' => 'tiny_slider',
        'theme path' => backdrop_get_path('module', 'tiny_slider') . '/theme',
        'theme file' => 'tiny_slider.theme.inc',
      ],
    ],
  ];
}
