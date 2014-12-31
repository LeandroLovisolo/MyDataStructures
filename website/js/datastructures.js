window.DataStructures =
[
  {
    name: 'AVL tree',
    functionNamePrefix: 'avl_',
    actions: [
      {
        type:         'integer',
        label:        'Insert',
        functionName: 'insert'
      },
      {
        type:         'random',
        label:        'Insert random',
        functionName: 'insert'
      },
      {
        type:         'void',
        label:        'Clear',
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
        label:        'Push',
        functionName: 'push'
      },
      {
        type:         'random',
        label:        'Push random',
        functionName: 'push'
      },
      {
        type:         'void',
        label:        'Pop',
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
        label:        'Insert',
        functionName: 'insert'
      },
      {
        type:         'random',
        label:        'Insert random',
        functionName: 'insert'
      },
      {
        type:         'integer',
        label:        'Remove',
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
