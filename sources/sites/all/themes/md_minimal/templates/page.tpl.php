<div id="page" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <!-- ______________________ HEADER _______________________ -->

  <div id="header">
    <div id="logo">
      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
        </a>
      <?php else: ?>
      	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
      <?php endif; ?>
    </div>

		<?php if ($main_menu): ?>
      <div id="navigation" class="menu <?php if (!empty($main_menu)) {print "with-primary";} if (!empty($secondary_menu)) {print " with-secondary";} ?>">
        <?php print theme('links', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('links', 'clearfix', 'main-menu')))); ?>
      </div>
    <?php endif; ?>
    
  </div> <!-- /header -->

  <!-- ______________________ MAIN _______________________ -->

  <div id="main" class="clearfix">
    <div id="content">
			<?php if ($breadcrumb || $title|| $messages || $tabs || $action_links): ?>
        <div id="content-header">

          <?php if ($page['highlight']): ?>
            <div id="highlight"><?php print render($page['highlight']) ?></div>
          <?php endif; ?>

          <?php if ($title): ?>
            <h1 class="title"><?php print $title; ?></h1>
          <?php endif; ?>

          <?php print $messages; ?>
          <?php print render($page['help']); ?>

          <?php if ($tabs): ?>
            <div class="tabs"><?php print render($tabs); ?></div>
          <?php endif; ?>

          <?php if ($action_links): ?>
            <ul class="action-links"><?php print render($action_links); ?></ul>
          <?php endif; ?>
          
        </div> <!-- /#content-header -->
      <?php endif; ?>

      <div id="content-area">
        <?php print render($page['content']) ?>
      </div>
    </div>
  </div> <!-- /main -->

  <!-- ______________________ FOOTER _______________________ -->

  <?php if ($page['footer']): ?>
    <div id="footer" class="clearfix">
      <div class="copyright">&copy; <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a> <?php print date('Y');?></div>
      <div class="credits">Powered by <a href="http://drupal.org">Drupal</a>. Theme by <a href="http://megadrupal.com">MegaDrupal</a></div>
    </div> <!-- /footer -->
  <?php endif; ?>

</div> <!-- /page -->