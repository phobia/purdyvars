<?php

    /**
    * Figure out what fields we have available
    * @param object $node The node object
    */
    function purdyvars_extract_fields($node) {

        $fields = array();
        $length = strlen(PURDYVARS_TARGET);

        foreach($node as $key => $row) {
            $crop = substr($key, 0, $length);
            if($crop == PURDYVARS_TARGET) {
                $settings = array(
                    'label' => $node['content'][$key]['#title'],
                    'render' => render($node['content'][$key])
                );
                $fields[$key] = array(
                    'data' => $row,
                    'settings' => $settings
                );
            }
        }
        
        return $fields;

    }
    

    /**
    * Apply the variable behaviour
    * @param array $fields 
    * @param string $prefix The prefix of our new variables. If this is field_ and suffix is blank, it will overwrite the variables set by Drupal. Which may mess with your existing templates.
    * @param string $suffix The suffix of our new variables.
    */
    function purdyvars_init_variables($fields, $prefix='field_', $suffix='') {
        
        $variables = array();
        
        foreach($fields as $name => $data) {
            $field_name = $prefix.str_replace(PURDYVARS_TARGET, '', $name).$suffix;
            $variables[$field_name] = new purdyvars_variable($fields[$name]['data']);
            $variables[$field_name]->label = $fields[$field_name]['settings']['label'];
            $variables[$field_name]->render = $fields[$field_name]['settings']['render'];
            
        }

        return $variables;    
    }
    
    
    /**
    * Add the variables to the node object
    * @param object $node The node object
    */
    function purdyvars_inject_variables(&$node, $variables) {
        foreach($variables as $name => $data) {
            $node[$name] = $data;
        }
    }
    
    
    /**
    * 
    */
    class purdyvars_variable implements iterator, countable, arrayAccess {
        
        private
            $data = null,
            $_current = 0;
    
        function __construct($data) {
            $this->set_data($data);
        }
        
        function set_data($data) {
            $this->data = $data;
        }

        function __toString() {
            return $this->data[0]['safe_value'];
        }
        
        /**
        * Iteration implementation
        */

        function current() {
            return $this->data[$this->current]['safe_value'];
        }
        
        function next() {
            $this->current += 1;
        }
        
        function rewind() {
            $this->current = 0;
        }
        
        function key() {
            return $this->current;
        }
        
        function valid() {
            return isset($this->data[$this->current]);
        }

        /**
        * Countable implementation
        */

        public function count() {
            return count($this->data);
        }
        
        /**
        * Array access implemetation
        */
    
        /**
        * is_array? since the arrayAccess is weak on this point for now, this will return wether the data is an array or not (has multiple values)
        */

        function is_array() {
            if(count($this->data) > 1) {
                return true;
            } else {
                return false;
            }
        }
        
        public function offsetSet($offset, $value) {
            if (is_null($offset)) {
                $this->data[] = $value;
            } else {
                $this->data[$offset] = $value;
            }
        }
        
        public function offsetExists($offset) {
            return isset($this->data);
        }
        
        public function offsetUnset($offset) {
            unset($this->data);
        }
        
        public function offsetGet($offset) {
            return isset($this->data[$offset]) ? $this->data[$offset]['safe_value'] : null;
        }        
        
        
    }
    