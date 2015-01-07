window.DataStructures =
[
  {
    name: 'Binary search tree',
    functionNamePrefix: 'bst_',
    operations: [
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
      },
      {
        type:         'void',
        label:        'Clear tree',
        functionName: 'clear'
      }
    ],
    files: [
      '/bst/bst.h',
    ]
  },
  {
    name: 'AVL tree',
    functionNamePrefix: 'avl_',
    operations: [
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
      },
      {
        type:         'void',
        label:        'Clear tree',
        functionName: 'clear'
      }
    ],
    files: [
      '/bst/bst.h',
      '/avl/avl.h',
      '/avl/avl.cpp'
    ]
  },
  {
    name: 'Heap',
    functionNamePrefix: 'heap_',
    operations: [
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
      },
      {
        type:         'void',
        label:        'Clear heap',
        functionName: 'clear'
      }
    ],
    files: [
      '/heap/heap.h',
      '/heap/heap.cpp'
    ]
  },
  {
    name: 'Skip list',
    functionNamePrefix: 'skiplist_',
    operations: [
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
      },
      {
        type:         'void',
        label:        'Clear skip list',
        functionName: 'clear'
      }
    ],
    files: [
      '/skiplist/skiplist.h',
      '/skiplist/skiplist.cpp'
    ]
  }
];
