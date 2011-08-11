<?php
// $Id: drig-gallery-view-full.tpl.php,v 1.0 2011/05/18 14:28:21 sas Exp $

/**
 * @file
 *
 * Available variables:
 * - $images: The images thumbnails.
 * - $image: Full current view image.
 *   
 * @see template_preprocess_drig_gallery_view_full()
 */
?>
<div class="drig-gallery-full">
	<div class="drig-view-container">
		<div class="drig-total-images">
			<?php print $total_images; ?>
		</div>
		<div class="drig-gallery-thumbnails">
			<?php if($nav): ?>
			<div class="drig-nav-wrapper">
				<?php print $nav; ?>
			</div>
			<?php endif; ?>
			<?php print $images; ?>
		</div>
		<div class="drig-gallery-image">
			<div class="drig-gallery-image-inner">
				<?php if ($image_title): ?>
				<h2 class="drig-image-title">
					<?php print $image_title; ?>
				</h2>
				<?php endif; ?>
				<?php print $original; ?>
				<div class="drig-gallery-image-wrapper">
					<?php print $image; ?>
				</div>
			</div>
		</div>
	</div>
	<div class="drig-load-container"></div>
</div>