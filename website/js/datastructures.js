window.DataStructures =
[
  {
    name: 'AVL tree',
    actions: [
      {
        type:         'integer',
        label:        'Insert',
        functionName: 'avl_insert'
      },
      {
        type:         'random',
        label:        'Insert random',
        functionName: 'avl_insert'
      },
      {
        type:         'void',
        label:        'Clear',
        functionName: 'avl_clear'
      }
    ],
    files: [
      'avl/bst.h',
      'avl/avl.h',
      'avl/avl.cpp'
    ]
  },
  {
    name: 'Heap',
    actions: [
      {
        type:         'integer',
        label:        'Push',
        functionName: 'heap_push'
      },
      {
        type:         'random',
        label:        'Push random',
        functionName: 'heap_push'
      },
      {
        type:         'void',
        label:        'Pop',
        functionName: 'heap_pop'
      }
    ],
    files: [
      'heap/heap.h',
      'heap/heap.cpp'
    ]
  },
  {
    name: 'Skip list',
    actions: [
      {
        type:         'integer',
        label:        'Insert',
        functionName: 'skip_list_insert'
      },
      {
        type:         'random',
        label:        'Insert random',
        functionName: 'skip_list_insert'
      },
      {
        type:         'integer',
        label:        'Remove',
        functionName: 'skip_list_remove'
      }
    ],
    files: [
      'skiplist/skiplist.h',
      'skiplist/skiplist.cpp'
    ]
  }
];
