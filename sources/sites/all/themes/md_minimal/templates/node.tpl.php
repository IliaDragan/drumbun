<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>">
	<?php if (!$page): ?>
		<?php if (render($content['field_image'])): ?>
      <div class="md-image"><?php print render($content['field_image']);?></div>
    <?php endif; ?>
    <div class="md-content">
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      
			<?php if ($display_submitted): ?>
        <div class="submitted"><?php print $date; ?> — <?php print $name; ?></div>
      <?php endif; ?>
    
      <div class="content">
        <?php 
          hide($content['field_image']);
          print render($content);
         ?>
      </div>
    </div> <!-- /md-content-->
    
  <?php else: ?>
    <?php print $user_picture; ?>
        
    <?php if ($display_submitted): ?>
      <div class="submitted"><?php print $date; ?> — <?php print $name; ?></div>
    <?php endif; ?>
  
    <div class="content">
      <?php 
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        //hide($content['field_image']);
        print render($content);
       ?>
    </div>
    
    <?php if (!empty($content['links']['terms'])): ?>
      <div class="terms"><?php print render($content['links']['terms']); ?></div>
    <?php endif;?>
    
    <?php if (!empty($content['links'])): ?>
      <div class="links"><?php print render($content['links']); ?></div>
    <?php endif; ?>
  <?php endif; ?>
</div> <!-- /node-->

<?php print render($content['comments']); ?>