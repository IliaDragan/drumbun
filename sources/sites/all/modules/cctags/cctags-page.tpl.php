<?php
/*
*  $content -- cctags content (all term for page
*  $cctid   -- cctags item id
*  $pager   -- if amount < count all terms view pager
*/
?>
<div class="cctags cctags-page wrapper<?php print $extra_class;?>">
<?php print render($content); ?>
</div>
<div>
<?php print render($pager); ?>
</div>