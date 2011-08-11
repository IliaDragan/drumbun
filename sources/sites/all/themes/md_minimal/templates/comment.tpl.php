<div class="<?php print $classes . ' ' . $zebra; ?> clearfix">
	<?php if ($picture) : ?><div class="avatar"><?php print $picture ?></div><?php endif; ?>
  <div class="commentinner">
    <h3 class="title"><?php print $title ?></h3>
    <?php if ($new) : ?>
      <span class="new"><?php print drupal_ucfirst($new) ?></span>
    <?php endif; ?>
  
    <div class="submitted"><?php print $created; ?> — <?php print $author; ?></div>
    
    <div class="content">
      <?php 
        hide($content['links']); 
        print render($content);
        ?>
      <?php if ($signature): ?>
        <div class="signature"><?php print $signature ?></div>
      <?php endif; ?>
    </div>
    
    <?php if (!empty($content['links'])): ?>
      <div class="links"><?php print render($content['links']); ?></div>
    <?php endif; ?>
  </div>
</div> <!-- /comment -->