var concat = require('broccoli-concat');
var mergeTrees = require('broccoli-merge-trees');
var compileLess = require('broccoli-less-single');

var jsTree = mergeTrees(['bower_components', 'js']);
var appJs = concat(jsTree, {
  inputFiles: ['jquery/dist/jquery.js',
               'bootstrap/dist/js/bootstrap.js',
               'handlebars/handlebars.js',
               'ember/ember.js',
               'slugify/slugify.js',
               'google-code-prettify/src/prettify.js',
               'bin.js',
               'datastructures.js',
               'application.js'],
  outputFile: '/assets/app.js'
});

var lessTree = mergeTrees(['bower_components/bootstrap/less', 'styles']);
var cssTree = mergeTrees(['bower_components',
                          compileLess(lessTree, 'styles.less', 'styles.css')]);
var appCss = concat(cssTree, {
  inputFiles: ['google-code-prettify/src/prettify.css',
               'styles.css'],
  outputFile: '/assets/app.css'
});

module.exports = mergeTrees([appJs, appCss, 'public']);
