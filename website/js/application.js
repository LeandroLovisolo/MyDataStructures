/////////////////////////////////////////////////
// Application                                 //
/////////////////////////////////////////////////

window.App = Ember.Application.create();

App.Router.map(function() {
  this.route('data-structure', { path: '/data-structures/:slug' }, function() {
    this.route('file', { path: '/files/:file_slug' });
  });
  this.route('about');
  this.route('catch-all', { path: '/*wildcard' });
});

/////////////////////////////////////////////////
// Views                                       //
/////////////////////////////////////////////////

Ember.LinkView.reopen({
  attributeBindings: ['role']
});

App.SubmitIntegerOperationView = Ember.View.extend({
  tagName: 'button',
  classNames: ['btn', 'btn-default'],
  click: function() {
    this.get('controller').send('execute');
  },
  focusOut: function() {
    this.get('controller').send('focusOut');
  }
});

App.SourceCodeView = Ember.View.extend({
  template: Ember.Handlebars.compile('{{view.code}}'),
  tagName: 'pre',
  classNames: 'code prettyprint lang-cpp',
  code: '',
  _initialize: function() {
    prettyPrint();
  }.on('didInsertElement'),
  codeChanged: function() {
    this.$().removeClass('prettyprinted')
            .text(this.get('code'));
    prettyPrint();
  }.observes('code')
});

/////////////////////////////////////////////////
// Components                                  //
/////////////////////////////////////////////////

App.PopOverComponent = Ember.Component.extend({
  _initialize: function() {
    this.$().popover({
      content: this.get('content'),
      placement: 'bottom',
      trigger: 'manual'
    });
  }.on('didInsertElement'),
  visibleChanged: function() {
    this.$().popover(this.get('visible') ? 'show' : 'hide');
  }.observes('visible')
});

/////////////////////////////////////////////////
// Routes                                      //
/////////////////////////////////////////////////

App.ApplicationRoute = Ember.Route.extend({
  model: function() {
    var dataStructures = [];

    DataStructures.forEach(function(dataStructure) {
      var dataStructureObj = App.DataStructure.create({
        name: dataStructure.name,
        basePath: dataStructure.basePath,
        functionNamePrefix: dataStructure.functionNamePrefix
      });

      var operations = dataStructure.operations.map(function(operation) {
        return App.Operation.create({
          dataStructure: dataStructureObj,
          type: operation.type,
          label: operation.label,
          functionName: operation.functionName
        });
      });

      var files = dataStructure.files.map(function(path) {
        return App.File.create({
          dataStructure: dataStructureObj,
          path: path
        });
      });

      dataStructureObj.set('operations', operations);
      dataStructureObj.set('files', files);

      dataStructures.push(dataStructureObj);
    });

    return dataStructures;
  }
});

App.IndexRoute = Ember.Route.extend({
  beforeModel: function() {
    var dataStructures = this.modelFor('application');
    this.transitionTo('data-structure', dataStructures.get('firstObject'));
  }
});

App.DataStructureRoute = Ember.Route.extend({
  model: function(params) {
    var dataStructures = this.modelFor('application');
    return dataStructures.findBy('slug', params.slug);
  },
  serialize: function(model) {
    return { slug: model.get('slug') };
  }
});

App.DataStructureFileRoute = Ember.Route.extend({
  model: function(params) {
    var dataStructure = this.modelFor('data-structure');
    return dataStructure.get('files').findBy('slug', params.file_slug);
  },
  serialize: function(model) {
    return { file_slug: model.get('slug') };
  }
});

App.CatchAllRoute = Ember.Route.extend({
  beforeModel: function() {
    this.transitionTo('index');
  }
});

//////////////////////////////////////////////////
// Controllers                                  //
//////////////////////////////////////////////////

App.DataStructureController = Ember.ObjectController.extend({
  needs: 'application',
  dataStructures: Ember.computed.alias('controllers.application')
});

App.OperationController = Ember.ObjectController.extend({
  parameter: '',
  hasErrors: false,
  _parameterChanged: function() {
    this.set('hasErrors', false);
  }.observes('parameter'),
  validateIntegerParameter: function() {
    return /^\d+$/.test(this.get('parameter').trim());
  },
  actions: {
    execute: function() {
      if( this.get('type') == 'integer' &&
         !this.validateIntegerParameter()) {
        this.set('hasErrors', true);
      } else {
        this.set('hasErrors', false);
        this.get('model').execute(this.get('parameter'));
      }
    },
    focusOut: function() {
      this.set('hasErrors', false);
    }
  },
});

/////////////////////////////////////////////////
// Models                                      //
/////////////////////////////////////////////////

App.DataStructure = Ember.Object.extend({
  init: function() {
    this.print();
  },
  name: '',
  functionNamePrefix: '',
  operations: [],
  basePath: '',
  files: [],
  output: '',
  slug: function() {
    return slugify(this.get('name'));
  }.property('name'),
  print: function() {
    var functionName = this.get('functionNamePrefix') + 'print';
    var printFunction = Module.cwrap(functionName, 'string', []);
    this.set('output', printFunction());
  }
});

App.Operation = Ember.Object.extend({
  dataStructure: null,
  type: '',
  label: '',
  functionName: '',
  isVoid: Ember.computed.equal('type', 'void'),
  isInteger: Ember.computed.equal('type', 'integer'),
  isRandom: Ember.computed.equal('type', 'random'),
  execute: function(parameter) {
    var operationFunctionName = this.get('dataStructure.functionNamePrefix') +
                                this.get('functionName');

    var argumentTypes = null, operationParameter = null;
    if(this.get('isVoid')) {
      argumentTypes = [];
    } else {
      argumentTypes = ['number'];
      if(this.get('isInteger')) {
        operationParameter = parameter;
      } else {
        operationParameter = parseInt(Math.random() * 100);
      }
    }

    var operationFunction = Module.cwrap(operationFunctionName,
                                         'void',
                                         argumentTypes);
    if(this.get('isVoid')) {
      operationFunction();
    } else {
      operationFunction(operationParameter);
    }

    this.get('dataStructure').print();
  }
});

App.File = Ember.Object.extend({
  init: function() {
    var self = this;
    $.ajax({ url: 'src/' +
                  this.get('dataStructure.basePath') +
                  this.get('path') })
     .then(function(response) {
       self.set('contents', response);
     });
  },
  dataStructure: null,
  path: '',
  contents: '',
  slug: function() {
    return encodeURIComponent(this.get('path'));
  }.property('path')
});
