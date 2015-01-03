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
               'bin.js',
               'datastructures.js',
               'application.js'],
  outputFile: '/assets/app.js'
});

var lessTree = mergeTrees(['bower_components/bootstrap/less', 'styles']);
var appCss = compileLess(lessTree, 'styles.less', 'assets/app.css');

module.exports = mergeTrees([appJs, appCss, 'public']);
