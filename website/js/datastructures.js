window.DataStructures =
[
  {
    name: 'AVL tree',
    functionNamePrefix: 'avl_',
    actions: [
      {
        type:         'integer',
        label:        'Insert a new item',
        functionName: 'insert'
      },
      {
        type:         'random',
        label:        'Insert a random item',
        functionName: 'insert'
      },
      {
        type:         'void',
        label:        'Clear tree',
        functionName: 'clear'
      }
    ],
    basePath: 'avl/',
    files: [
      'bst.h',
      'avl.h',
      'avl.cpp'
    ]
  },
  {
    name: 'Heap',
    functionNamePrefix: 'heap_',
    actions: [
      {
        type:         'integer',
        label:        'Push a new item',
        functionName: 'push'
      },
      {
        type:         'random',
        label:        'Push a random item',
        functionName: 'push'
      },
      {
        type:         'void',
        label:        'Pop an item',
        functionName: 'pop'
      }
    ],
    basePath: 'heap/',
    files: [
      'heap.h',
      'heap.cpp'
    ]
  },
  {
    name: 'Skip list',
    functionNamePrefix: 'skiplist_',
    actions: [
      {
        type:         'integer',
        label:        'Insert a new item',
        functionName: 'insert'
      },
      {
        type:         'random',
        label:        'Insert a random item',
        functionName: 'insert'
      },
      {
        type:         'integer',
        label:        'Remove an item',
        functionName: 'remove'
      }
    ],
    basePath: 'skiplist/',
    files: [
      'skiplist.h',
      'skiplist.cpp'
    ]
  }
];
