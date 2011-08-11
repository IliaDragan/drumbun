<?php
// Form override fo theme settings
function md_minimal_form_system_theme_settings_alter(&$form, $form_state) {

  $form['options_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theme Specific Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );
  
  $form['options_settings']['clear_registry'] = array(
    '#type' => 'checkbox',
    '#title' =>  t('Rebuild theme registry on every page.'),
    '#description'   =>t('During theme development, it can be very useful to continuously <a href="!link">rebuild the theme registry</a>. WARNING: this is a huge performance penalty and must be turned off on production websites.', array('!link' => 'http://drupal.org/node/173880#theme-registry')),
    '#default_value' => theme_get_setting('clear_registry'),
  );
	
	$form['options_settings']['md_minimal_analytics'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Google Analytics Code'),
    '#description'   => t('You can paste your Google Analytics or other tracking code in this box. This will be automatically added to the footer.'),
    '#default_value' => theme_get_setting('md_minimal_analytics'),
  );
	
	$form['options_settings']['md_minimal_css'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Custom CSS'),
    '#description'   => t('Want to add any custom CSS code? Put in here, and the rest is taken care of. This overrides any other stylesheets. eg: a.button {color:green}'),
    '#default_value' => theme_get_setting('md_minimal_css'),
  );
}