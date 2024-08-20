/**
 * @file
 */

(function ($) {
  Backdrop.behaviors.tinyslider = {
    attach(context) {
      $(context)
        .find('.tiny-slider-wrapper')
        .once('tiny-slider')
        .each(function () {
          const $table = $(this);
          processingCallback($table[0]);
        });
    }
  };

  function processingCallback(sliderContainer) {
    opt = JSON.parse(sliderContainer.getAttribute('data-settings'));
    opt.container = sliderContainer;
    var slider = tns(opt);
  }
})(jQuery);
