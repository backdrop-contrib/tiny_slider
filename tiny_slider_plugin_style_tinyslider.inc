<?php

/**
 * Style plugin to render items as Tiny slides.
 *
 * @ingroup views_style_plugins
 */
class tiny_slider_plugin_style_tinyslider extends views_plugin_style {

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $settings = _tiny_slider_default_settings();
    if (is_array($settings)) {
      foreach ($settings as $k => $v) {
        $options[$k] = ['default' => $v];
      }
    }

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $hideOnAdvancedMode = [
      'visible' => [
        ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
      ],
    ];

    // Items.
    $form['items'] = [
      '#type' => 'number',
      '#step' => '.1',
      '#title' => t('Items'),
      '#default_value' => isset($this->options['items']) ? $this->options['items'] : '',
      '#description' => t('Maximum amount of items displayed at a time with the widest browser width.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // Gutter.
    $form['gutter'] = [
      '#type' => 'number',
      '#title' => t('Gutter'),
      '#default_value' => isset($this->options['gutter']) ? $this->options['gutter'] : '',
      '#description' => t('Gutter from items.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // Mode.
    $form['mode'] = [
      '#type' => 'select',
      '#title' => t('Mode'),
      '#options' => [
        'carousel' => t('Carousel'),
        'gallery' => t('Gallery'),
      ],
      '#default_value' => isset($this->options['mode']) ? $this->options['mode'] : '',
      '#description' => t('With carousel everything slides to the side, while gallery uses fade animations and changes all slides at once.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // Navigation.
    $form['nav'] = [
      '#type' => 'checkbox',
      '#title' => t('Navigation'),
      '#default_value' => isset($this->options['nav']) ? $this->options['nav'] : '',
      '#description' => t('Controls the display and functionalities of nav components (dots).'),
      '#states' => $hideOnAdvancedMode,
    ];
    // navPosition.
    $form['navPosition'] = [
      '#type' => 'select',
      '#title' => t('Navigation position'),
      '#options' => [
        'top' => t('Top'),
        'bottom' => t('Bottom'),
      ],
      '#default_value' => isset($this->options['navPosition']) ? $this->options['navPosition'] : '',
      '#description' => t('Display navigation above/below slides.'),
      '#states' => [
        'visible' => [
          ':input[name="style_options[nav]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // navAsThumbnails.
    $form['navAsThumbnails'] = [
      '#type' => 'checkbox',
      '#title' => t('Navigation as thumbnails'),
      '#default_value' => isset($this->options['navAsThumbnails']) ? $this->options['navAsThumbnails'] : '',
      '#description' => t('Use image thumbnails in navigation instead of dots.'),
      '#states' => [
        'visible' => [
          ':input[name="style_options[nav]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // Autoplay.
    $form['autoplay'] = [
      '#type' => 'checkbox',
      '#title' => t('Autoplay'),
      '#default_value' => isset($this->options['autoplay']) ? $this->options['autoplay'] : '',
      '#description' => t('Toggles the automatic change of slides.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // AutoplayHoverPause.
    $form['autoplayHoverPause'] = [
      '#type' => 'checkbox',
      '#title' => t('Pause on hover'),
      '#default_value' => $this->options['autoplayHoverPause'],
      '#description' => t('Pause autoplay on mouse hover.'),
      '#states' => [
        'visible' => [
          ':input[name="style_options[autoplay]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // AutoplayButtonOutput.
    $form['autoplayButtonOutput'] = [
      '#type' => 'checkbox',
      '#title' => t('Autoplay buttons'),
      '#default_value' => isset($this->options['autoplayButtonOutput']) ? $this->options['autoplayButtonOutput'] : '',
      '#description' => t('Turn off/on arrow autoplay buttons.'),
      '#states' => [
        'visible' => [
          ':input[name="style_options[autoplay]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // autoplayPosition.
    $form['autoplayPosition'] = [
      '#type' => 'select',
      '#title' => t('Autoplay position'),
      '#options' => [
        'top' => t('Top'),
        'bottom' => t('Bottom'),
      ],
      '#default_value' => isset($this->options['autoplayPosition']) ? $this->options['autoplayPosition'] : '',
      '#description' => t('Display autoplay controls above/below slides.'),
      '#states' => [
        'visible' => [
          ':input[name="style_options[autoplay]"]' => ['checked' => TRUE],
          ':input[name="style_options[autoplayButtonOutput]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // Autoplay text start.
    $form['autoplayTextStart'] = [
      '#type' => 'textfield',
      '#title' => t('Start Text'),
      '#default_value' => isset($this->options['autoplayTextStart']) ? $this->options['autoplayTextStart'] : '',
      '#states' => [
        'visible' => [
          ':input[name="style_options[autoplay]"]' => ['checked' => TRUE],
          ':input[name="style_options[autoplayButtonOutput]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // Autoplay text stop.
    $form['autoplayTextStop'] = [
      '#type' => 'textfield',
      '#title' => t('Stop Text'),
      '#default_value' => isset($this->options['autoplayTextStop']) ? $this->options['autoplayTextStop'] : '',
      '#states' => [
        'visible' => [
          ':input[name="style_options[autoplay]"]' => ['checked' => TRUE],
          ':input[name="style_options[autoplayButtonOutput]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // Controls.
    $form['controls'] = [
      '#type' => 'checkbox',
      '#title' => t('Controls'),
      '#default_value' => isset($this->options['controls']) ? $this->options['controls'] : '',
      '#description' => t('Controls the display and functionalities of (prev/next buttons).'),
      '#states' => $hideOnAdvancedMode,
    ];
    // controlsPosition.
    $form['controlsPosition'] = [
      '#type' => 'select',
      '#title' => t('Controls position'),
      '#options' => [
        'top' => t('Top'),
        'bottom' => t('Bottom'),
      ],
      '#default_value' => isset($this->options['controlsPosition']) ? $this->options['controlsPosition'] : '',
      '#description' => t('Display controls above/below slides.'),
      '#states' => [
        'visible' => [
          ':input[name="style_options[controls]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // Controls text prev.
    $form['controlsTextPrev'] = [
      '#type' => 'textfield',
      '#title' => t('Prev Text'),
      '#default_value' => isset($this->options['controlsTextPrev']) ? $this->options['controlsTextPrev'] : '',
      '#states' => [
        'visible' => [
          ':input[name="style_options[controls]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // Controls next text.
    $form['controlsTextNext'] = [
      '#type' => 'textfield',
      '#title' => t('Next Text'),
      '#default_value' => isset($this->options['controlsTextNext']) ? $this->options['controlsTextNext'] : '',
      '#states' => [
        'visible' => [
          ':input[name="style_options[controls]"]' => ['checked' => TRUE],
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => FALSE],
        ],
      ],
    ];
    // Slide by.
    $form['slideBy'] = [
      '#type' => 'textfield',
      '#title' => t('Slide by'),
      '#default_value' => isset($this->options['slideBy']) ? $this->options['slideBy'] : '',
      '#description' => t('Number of slides going on one "click". Enter a positive number or "page" to slide one page at a time.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // arrowKeys.
    $form['arrowKeys'] = [
      '#type' => 'checkbox',
      '#title' => t('Arrow Keys'),
      '#default_value' => isset($this->options['arrowKeys']) ? $this->options['arrowKeys'] : '',
      '#description' => t('Allows using arrow keys to switch slides.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // mouseDrag.
    $form['mouseDrag'] = [
      '#type' => 'checkbox',
      '#title' => t('Mouse Drag'),
      '#default_value' => isset($this->options['mouseDrag']) ? $this->options['mouseDrag'] : '',
      '#description' => t('Turn off/on mouse drag.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // Loop.
    $form['loop'] = [
      '#type' => 'checkbox',
      '#title' => t('Loop'),
      '#default_value' => isset($this->options['loop']) ? $this->options['loop'] : '',
      '#description' => t('Moves throughout all the slides seamlessly.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // Center.
    $form['center'] = [
      '#type' => 'checkbox',
      '#title' => t('Center'),
      '#default_value' => isset($this->options['center']) ? $this->options['center'] : '',
      '#description' => t('Center the active slide in the viewport.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // Speed.
    $form['speed'] = [
      '#type' => 'number',
      '#title' => t('Speed'),
      '#default_value' => isset($this->options['speed']) ? $this->options['speed'] : '',
      '#description' => t('Pagination speed in milliseconds.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // DimensionMobile.
    $form['dimensionMobile'] = [
      '#type' => 'number',
      '#title' => t('Mobile dimension'),
      '#default_value' => isset($this->options['dimensionMobile']) ? $this->options['dimensionMobile'] : '',
      '#description' => t('Set the mobile dimensions in px.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // ItemsMobile.
    $form['itemsMobile'] = [
      '#type' => 'number',
      '#step' => '.1',
      '#title' => t('Mobile items'),
      '#default_value' => isset($this->options['itemsMobile']) ? $this->options['itemsMobile'] : '',
      '#description' => t('Maximum amount of items displayed at mobile.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // DimensionDesktop.
    $form['dimensionDesktop'] = [
      '#type' => 'number',
      '#title' => t('Desktop dimension'),
      '#default_value' => isset($this->options['dimensionDesktop']) ? $this->options['dimensionDesktop'] : '',
      '#description' => t('Set the desktop dimension in px.'),
      '#states' => $hideOnAdvancedMode,
    ];
    // itemsDesktop.
    $form['itemsDesktop'] = [
      '#type' => 'number',
      '#step' => '.1',
      '#title' => t('Desktop items'),
      '#default_value' => isset($this->options['itemsDesktop']) ? $this->options['itemsDesktop'] : '',
      '#description' => t('Maximum amount of items displayed at desktop.'),
      '#states' => $hideOnAdvancedMode,
    ];

    // Advanced mode.
    $form['advancedMode'] = [
      '#type' => 'checkbox',
      '#title' => t('Advanced mode'),
      '#default_value' => $this->options['advancedMode'],
      '#description' => t('In advanced mode you can use JSON object to override config.'),
      '#attributes' => ['class' => ['tns--toggle-advanced-mode']],
    ];

    $form['configJson'] = [
      '#type' => 'textarea',
      '#title' => t('Use a JSON object to configure the slider'),
      '#default_value' => json_encode(json_decode($this->options['configJson']), JSON_PRETTY_PRINT),
      '#description' => t('Tiny Slider configuration expressed as JSON.<br />
        <b>WARNING:</b> this will override any existing settings'),
      '#rows' => 30,
      '#states' => [
        'visible' => [
          ':input[type="checkbox"].tns--toggle-advanced-mode' => ['checked' => TRUE],
        ],
      ],
    ];
  }

  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);
    $styleOptions = $form_state['values']['style_options']['slideBy'];
    if (!preg_match('~[0-9]+~', $styleOptions) && ($styleOptions !== 'page')) {
      form_error($form['slideBy'], t('@value is not right. The "Slide by" value should either be an Integer or equal to the term "page".', ['@value' => $styleOptions]));
    }
  }

}
