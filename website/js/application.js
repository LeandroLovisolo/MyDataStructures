/////////////////////////////////////////////////
// Application                                 //
/////////////////////////////////////////////////

window.App = Ember.Application.create();

App.Router.map(function() {
  this.route('data-structure', { path: '/data-structures/:slug' }, function() {
    this.route('file', { path: '/files/:file_slug' });
  });
  this.route('about');
});

Ember.LinkView.reopen({
  attributeBindings: ['role']
});

/////////////////////////////////////////////////
// Routes                                      //
/////////////////////////////////////////////////

App.ApplicationRoute = Ember.Route.extend({
  model: function() {
    var dataStructures = [];

    DataStructures.forEach(function(dataStructure) {
      dataStructures.push(App.DataStructure.create({
        name: dataStructure.name,
        actions: dataStructure.actions.map(function(action) {
          return App.Action.create(action);
        }),
        files: dataStructure.files.map(function(path) {
          return App.File.create({ path: path });
        })
      }));
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

//////////////////////////////////////////////////
// Controllers                                  //
//////////////////////////////////////////////////

App.DataStructureController = Ember.ObjectController.extend({
  needs: 'application',
  dataStructures: Ember.computed.alias('controllers.application')
});

App.DataStructureIndexController = Ember.ObjectController.extend({
  executeAction: function(action, parameter) {
    this.set('output', 'Action ' + action.get('label') + ' executed.');
  }
});

App.ActionController = Ember.ObjectController.extend({
  parameter: '',
  actions: {
    executeAction: function() {
      this.target.executeAction(this.get('model'), this.get('parameter'));
    }
  },
});

/////////////////////////////////////////////////
// Models                                      //
/////////////////////////////////////////////////

App.DataStructure = Ember.Object.extend({
  name: '',
  actions: [],
  files: [],
  output: '',
  slug: function() {
    return slugify(this.get('name'));
  }.property('name')
});

App.Action = Ember.Object.extend({
  type: '',
  label: '',
  functionName: '',
  isVoid: Ember.computed.equal('type', 'void'),
  isInteger: Ember.computed.equal('type', 'integer'),
  isRandom: Ember.computed.equal('type', 'random'),
});

App.File = Ember.Object.extend({
  path: '',
  slug: function() {
    return slugify(this.get('path'));
  }.property('path')
});
