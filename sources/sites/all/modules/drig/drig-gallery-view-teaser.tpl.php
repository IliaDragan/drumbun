<?php
// $Id: drig-gallery-view-teaser.tpl.php,v 1.0 2011/05/18 14:28:21 sas Exp $

/**
 * @file
 *
 * Available variables:
 * - $image: The gallery images thumbnails.
 * - $gallery_title: Gallery title.
 *   
 * @see template_preprocess_drig_gallery_view_teaser()
 */
?>
<div class="drig-gallery">
	<div class="drig-total-images">
		<?php print $total_images; ?>
	</div>	<div class="drig-gallery-thumbnail">
		<?php print $image; ?>
	</div>
</div>