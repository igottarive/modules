(function ($) {
  Drupal.behaviors.quiz_extension = {
    attach: function (context, settings) {

      $(".progressbar").each(function() {
        var element = this;
        $(element).progressbar({
          value: parseInt($(element).attr("value")),
          max: parseInt($(element).attr("max"))
        });
      });
    }
  };
}(jQuery));
