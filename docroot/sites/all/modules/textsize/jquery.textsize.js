// $Id: jquery.textsize.js,v 1.3 2009/12/10 23:16:50 christianzwahlen Exp $

(function($) {
  $(document).ready(function(){
    $("a.ts_increase_variable").attr({ href: "#" });
    $("a.ts_decrease_variable").attr({ href: "#" });
    $("a.ts_normal_variable").attr({ href: "#" });
    $("a.ts_increase_fix").attr({ href: "#" });
    $("a.ts_decrease_fix").attr({ href: "#" });
    $("a.ts_normal_fix").attr({ href: "#" });
    function textsizeDisplayCalc(ts_v) {
      if (textsizeDisplay == 1) {
        ts_c = (100 * ts_v / textsizeNormal);
        return Math.round(ts_c);
      }
      else {
        return ts_v;
      }
    }
    function textsizeIncrease(ts_a, ts_b) {
      if (ts_a == textsizeMaximum) {
        return ts_a;
      }
      else {
        return 1*ts_a + 1*textsizeIncrement;
      }
    }
    function textsizeDecrease(ts_a, ts_b) {
      if (ts_a == textsizeMinimum) {
        return ts_a;
      }
      else {
        return 1*ts_a - 1*textsizeIncrement;
      }
    }
    function TSremoveBC(){
      var tsElement = $(textsizeElement + textsizeElementClass);
      var tsClasses = tsElement.attr('class').split(' ');
      for( var i in tsClasses ){
        if( tsClasses[i].substring(0,8) == 'textsize' ){
          tsElement.removeClass( tsClasses[i] );
          break;
        }
      }
    }
    function tsIncrease(){
      TSremoveBC();
      $("#textsize_current").empty();
      $("#textsize_current").append((textsizeNormalDisplay + textsizeIncrementDisplay) + '%');
      $("#textsize_current").attr({ title: textsizeCurrentText + ": " + (textsizeNormalDisplay + textsizeIncrementDisplay) + '%'});
      $(textsizeElement + textsizeElementClass).addClass('textsize-' + (textsizeNormal + textsizeIncrement));
      $(textsizeElement + textsizeElementClass).css("font-size", (textsizeNormal + textsizeIncrement) + "%");
      $.cookie('textsize', textsizeIncrease(textsizeNormalDisplay, textsizeIncrementDisplay), { expires: textsizeCookieExpires, path: textsizeCookieDomain});
      return false;
    }
    function tsDecrease(){
      TSremoveBC();
      $("#textsize_current").empty();
      $("#textsize_current").append((textsizeNormalDisplay - textsizeIncrementDisplay) + '%');
      $("#textsize_current").attr({ title: textsizeCurrentText + ": " + (textsizeNormalDisplay - textsizeIncrementDisplay) + '%'});
      $(textsizeElement + textsizeElementClass).addClass('textsize-' + (textsizeNormal - textsizeIncrement));
      $(textsizeElement + textsizeElementClass).css("font-size", (textsizeNormal - textsizeIncrement) + "%");
      $.cookie('textsize', textsizeDecrease(textsizeNormalDisplay, textsizeIncrementDisplay), { expires: textsizeCookieExpires, path: textsizeCookieDomain});
      return false;
    }
    function tsNormal(){
      TSremoveBC();
      $("#textsize_current").empty();
      $("#textsize_current").append(textsizeNormalDisplay + '%');
      $("#textsize_current").removeClass('error');
      $("#textsize_current").attr({ title: textsizeCurrentText + ": " + textsizeNormalDisplay + '%'});
      $(textsizeElement + textsizeElementClass).addClass('textsize-' + textsizeNormal);
      $(textsizeElement + textsizeElementClass).css("font-size", textsizeNormal + "%");
      $.cookie('textsize', textsizeNormal, { expires: textsizeCookieExpires, path: textsizeCookieDomain});
      return false;
    }
    function tsForm() {
      var ts_val = $("#edit-textsize-select").val();
      var ts_val_d = textsizeDisplayCalc($("#edit-textsize-select").val());
      TSremoveBC();
      $.cookie('textsize', ts_val, { expires: textsizeCookieExpires, path: textsizeCookieDomain});
      $(textsizeElement + textsizeElementClass).addClass("textsize-" + ts_val);
      $("#textsize_current").empty();
      $("#textsize_current").append(ts_val_d + '%');
      $("#textsize_current").attr({ title: textsizeCurrentText + ": " + ts_val_d + '%'});
      $(textsizeElement + textsizeElementClass).addClass('textsize-' + ts_val);
      $(textsizeElement + textsizeElementClass).css("font-size", ts_val + "%");
    }
    $("a.ts_increase_variable[href=#]").click(
      function (){
        if ($.cookie("textsize") && $.cookie("textsize") < textsizeMaximum) {
          TSremoveBC();
          $.cookie('textsize', textsizeIncrease($.cookie("textsize"), textsizeIncrement), { expires: textsizeCookieExpires, path: textsizeCookieDomain});
          $("#textsize_current").empty();
          $("#textsize_current").append( textsizeDisplayCalc($.cookie("textsize")) + '%');
          $("#textsize_current").attr({ title: textsizeCurrentText + ": " + textsizeDisplayCalc($.cookie("textsize")) + '%'});
          $("#textsize_current").removeClass('error');
          $(textsizeElement + textsizeElementClass).addClass('textsize-' + $.cookie("textsize"));
          $(textsizeElement + textsizeElementClass).css("font-size", $.cookie("textsize") + "%");
          return false;
        }
        else if ($.cookie("textsize") && ($.cookie("textsize") == textsizeMaximum) && textsizeReset == 0) {
          $("#textsize_current").empty();
          $("#textsize_current").append( '<abbr title="' + Drupal.t('Maximum') + '" class="textsize">' + Drupal.t('Max.') + '</abbr> ' + textsizeDisplayCalc(textsizeMaximum) + '%');
          $("#textsize_current").addClass('error');
          return false;
        }
        else if ($.cookie("textsize") && ($.cookie("textsize") == textsizeMaximum) && textsizeReset == 1) {
          tsNormal()
          return false;
        }
      }
    );
    $("a.ts_increase_fix[href=#]").click(
      function (){
        if ($.cookie("textsize") && $.cookie("textsize") < (textsizeNormal + textsizeIncrement)) {
          TSremoveBC();
          $.cookie('textsize', (textsizeNormal + textsizeIncrement), { expires: textsizeCookieExpires, path: textsizeCookieDomain});
          $("#textsize_current").empty();
          $("#textsize_current").append( textsizeDisplayCalc($.cookie("textsize")) + '%');
          $("#textsize_current").attr({ title: textsizeCurrentText + ": " + textsizeDisplayCalc($.cookie("textsize")) + '%'});
          $("#textsize_current").removeClass('error');
          $(textsizeElement + textsizeElementClass).addClass('textsize-' + (textsizeNormal + textsizeIncrement));
          $(textsizeElement + textsizeElementClass).css("font-size", (textsizeNormal + textsizeIncrement) + "%");
          return false;
        }
        else if ($.cookie("textsize") && $.cookie("textsize") == (textsizeNormal + textsizeIncrement)) {
          $("#textsize_current").empty();
          $("#textsize_current").append( '<abbr title="' + Drupal.t('Maximum') + '" class="textsize">' + Drupal.t('Max.') + '</abbr> ' + textsizeDisplayCalc((textsizeNormal + textsizeIncrement)) + '%');
          $("#textsize_current").addClass('error');
          return false;
        }
        else {
          tsIncrease()
        }
      }
    );
    $("a.ts_decrease_variable[href=#]").click(
      function (){
        if ($.cookie("textsize") && $.cookie("textsize") > textsizeMinimum) {
          TSremoveBC();
          $.cookie('textsize', textsizeDecrease($.cookie("textsize"), textsizeIncrement), { expires: textsizeCookieExpires, path: textsizeCookieDomain});
          $("#textsize_current").empty();
          $("#textsize_current").append( textsizeDisplayCalc($.cookie("textsize")) + '%');
          $("#textsize_current").attr({ title: textsizeCurrentText + ": " + textsizeDisplayCalc($.cookie("textsize")) + '%'});
          $("#textsize_current").removeClass('error');
          $(textsizeElement + textsizeElementClass).addClass('textsize-' + $.cookie("textsize"));
          $(textsizeElement + textsizeElementClass).css("font-size", $.cookie("textsize") + "%");
          return false;
        }
        else if ($.cookie("textsize") && ($.cookie("textsize") == textsizeMinimum) && textsizeReset == 0) {
          $("#textsize_current").empty();
          $("#textsize_current").append( '<abbr title="' + Drupal.t('Minimum') + '" class="textsize">' + Drupal.t('Min.') + '</abbr> ' + textsizeDisplayCalc(textsizeMinimum) + '%');
          $("#textsize_current").addClass('error');
          return false;
        }
        else if ($.cookie("textsize") && ($.cookie("textsize") == textsizeMinimum) && textsizeReset == 1) {
          tsNormal()
          return false;
        }
      }
    );
    $("a.ts_decrease_fix[href=#]").click(
      function (){
        if ($.cookie("textsize") && $.cookie("textsize") > (textsizeNormal - textsizeIncrement)) {
          TSremoveBC();
          $.cookie('textsize', (textsizeNormal - textsizeIncrement), { expires: textsizeCookieExpires, path: textsizeCookieDomain});
          $("#textsize_current").empty();
          $("#textsize_current").append( textsizeDisplayCalc($.cookie("textsize")) + '%');
          $("#textsize_current").attr({ title: textsizeCurrentText + ": " + textsizeDisplayCalc($.cookie("textsize")) + '%'});
          $("#textsize_current").removeClass('error');
          $(textsizeElement + textsizeElementClass).addClass('textsize-' + (textsizeNormal - textsizeIncrement));
          $(textsizeElement + textsizeElementClass).css("font-size", (textsizeNormal - textsizeIncrement) + "%");
          return false;
        }
        else if ($.cookie("textsize") && $.cookie("textsize") == (textsizeNormal - textsizeIncrement)) {
          $("#textsize_current").empty();
          $("#textsize_current").append( '<abbr title="' + Drupal.t('Minimum') + '" class="textsize">' + Drupal.t('Min.') + '</abbr> ' + textsizeDisplayCalc((textsizeNormal - textsizeIncrement)) + '%');
          $("#textsize_current").addClass('error');
          return false;
        }
        else {
          tsDecrease()
        }
      }
    );
    $("a.ts_normal_variable[href=#]").click(
      function (){
        tsNormal();
        return false;
      }
    );
    $("a.ts_normal_fix[href=#]").click(
      function (){
        tsNormal();
        return false;
      }
    );
    $("#edit-textsize-select").change(tsForm);
    $("#edit-textsize-submit").hide();
    $("img.ts_rollover").hover(
      function(){
        if($(this).attr("src").indexOf("16_hover") == -1) {
          var newSrc = $(this).attr("src").replace("16.gif","16_hover.gif#hover");
          $(this).attr("src",newSrc);
        }
      },
      function(){
        if($(this).attr("src").indexOf("16_hover.gif#hover") != -1) {
          var oldSrc = $(this).attr("src").replace("16_hover.gif#hover","16.gif");
          $(this).attr("src",oldSrc);
        }
        else if($(this).attr("src").indexOf("16_focus.gif#focus") != -1) {
          var oldSrc = $(this).attr("src").replace("16_focus.gif#focus","16.gif");
          $(this).attr("src",oldSrc);
        }
      }
    );
    $("a.ts_rollover").focus(
      function(){
        var tsIMG = $(this).children("img");
        if($(tsIMG).attr("src").indexOf("16_hover.gif#hover") != -1) {
          var newSrc = $(tsIMG).attr("src").replace("16_hover.gif#hover","16_focus.gif#focus");
          $(tsIMG).attr("src",newSrc);
        }
      }
    );
  });
})(jQuery);
