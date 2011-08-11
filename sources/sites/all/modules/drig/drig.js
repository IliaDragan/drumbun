// $Id: drig.js,v 1.0 2011/05/21 20:25:21 sas Exp $
(function ($) {
	Drupal.behaviors.drig = {
			attach: function (context) {
				throbber = $('<span class="drig-throbber">in process</span>');
				navThrobber = $('<span class="drig-nav-throbber">in process</span>');
				function drigAttachNavEvent(){
					$('.drig-nav a').bind('click', 
							function(){
								loadNav(this);
								return false;
							}  
					);	
				}
				function drigAttachThumbEvent(){
				$('.drig-thumbnail-list a.drig-viewed-image').bind('click', 
					function(){
						return false;
				});
				$('.drig-thumbnail-list a:not(.drig-viewed-image)').bind('click', 
					function(){
						loadImage(this);
						return false;
				});
				$('.drig-thumbnail-list a:not(.drig-viewed-image)').bind('mouseenter', 
					function(){
						loadImage(this);
					}  
				);
				}
				function loadImage(elem){
					$('.drig-thumbnail-list a').unbind('mouseenter');
					$('.drig-nav a').unbind('click');
					$('.drig-nav a').bind('click', function(){ return false; });
					$('.drig-thumbnail-list a:not(.drig-viewed-image)').unbind('click');
					$('.drig-thumbnail-list a:not(.drig-viewed-image)').bind('click', function(){
						return false;
					});
					$('.drig-viewed-image').removeClass('drig-viewed-image');
					$(elem).addClass('drig-viewed-image');
					$('.drig-thumb-hover').removeClass('drig-thumb-hover');
					$(elem).addClass('drig-thumb-hover');
					var throbTarget = $('.drig-gallery-image-wrapper');
					$('.drig-gallery-image-wrapper img').addClass('drig-viewed-image');
					$('body').append(throbber.css({
						'top':throbTarget.offset().top + (throbTarget.height() - 32)/2, 
						'left':throbTarget.offset().left + (throbTarget.width() - 32)/2
						}));
					throbber.show();
					$('.drig-load-container > *').remove();
					$('.drig-load-container').load($(elem).attr('href') + ' .drig-gallery-image-inner > *', 
						function(response, status, xhr){
							if(status != 'error'){
								$('.drig-load-container img').load(
									function(){
									$('.drig-gallery-image-inner > *').remove();
									$('.drig-gallery-image-inner').html($('.drig-load-container > *')).hide().fadeIn("slow");
									drigAttachThumbEvent();
									drigAttachNavEvent();
									throbber.remove();
								});
							} else {
							 throbber.remove();
							 return flase;
							}
						}
					);
				}
				function loadNav(elem){
				$('.drig-nav').addClass('drig-nav-process');
				var list = $(elem).parent().parent();
				$('body').append(navThrobber.css({
					'top':list.offset().top + (list.height() - 18)/2, 
					'left':list.offset().left + (list.width() - 18)
					}));
					navThrobber.show();
					$('.drig-load-container > *').remove();
					$('.drig-load-container').load($(elem).attr('href') + ' .drig-view-container > *',
							function(response, status, xhr){
								if(status != 'error'){  
									$('.drig-load-container img:last').load(
											function(){
												$('.drig-view-container > *').remove();
												$('.drig-view-container').html($('.drig-load-container > *')).hide().fadeIn("slow");
												drigAttachNavEvent();
												drigAttachThumbEvent();
												navThrobber.remove();
									});
								} else {
									navThrobber.remove();
									return false;
								}
							}
					);
				}
				drigAttachNavEvent();
				drigAttachThumbEvent();
			}
	}; 
})(jQuery);