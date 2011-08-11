<?php
// $Id: drig.admin.inc,v 1 2011/05/17 19:59:43 sas Exp $
/**
 * admin functions.
 */
function drig_settings() {
	$node_types = node_type_get_types();
	foreach($node_types as $key => $type){
		$opt_types[$key] = $type->name;
	}
	// Gather bundle information.
  	$instances = field_info_instances('node');
 	unset($instances['image_gallery']);
	foreach($instances as $bundle => $fields){
		foreach($fields as $field_name => $field){
		if($field['widget']['type'] == 'image_image'){
		$bundles_fields[$bundle][$field_name] = $field['label'];
		}
		}
	}
	if($bundles_fields){
	foreach($bundles_fields as $bundle => $fields){
		$form['drig_fields_' . $bundle] = array(
		'#type' => 'fieldset',
		'#description' => t('Include for fields.'),
		'#title' => $node_types[$bundle]->name,
		);
		$form['drig_fields_' . $bundle]['drig_fields_' . $bundle] = array(
		'#type' => 'select',
		'#default_value' => variable_get('drig_fields_' . $bundle, 0),
		'#options' => array_merge(array(t('None')),$fields),
		);
	}
	}
	$styles = image_styles();
	foreach($styles as $style_name => $style){
		$styles_opt[$style_name] = $style_name;
	}
	$form['drig_thumbnail_image_style'] = array(
	'#type' => 'select',
	'#title' => t('Thumbnail image style'),
	'#default_value' => variable_get('drig_thumbnail_image_style', DRIG_THUMB_IS_NAME),
	'#options' => $styles_opt
	);
	$form['drig_count_on_page'] = array(
	'#type' => 'textfield',
    '#title' => t('Count image on page for navigation.'),
	'#description' => t('0 - not use navigator.'),
    '#default_value' => variable_get('drig_count_on_page', 5),
    '#size' => 3,
	);
	return system_settings_form($form);
}