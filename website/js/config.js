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
    ],
    helpText:
      '<p>' +
      '  <strong>Tip:</strong> Click <em>Insert a random item</em>' +
      '  repeatedly to quickly build a binary search tree.' +
      '</p>' +
      '<hr>' +
      '<p>' +
      '  A <a href="http://en.wikipedia.org/wiki/Binary_search_tree">binary' +
      '  search tree</a> is a binary tree where each node has a comparable' +
      '  key and satisfies the restriction that the key in any node is' +
      '  larger than the keys in all nodes in that node\'s left sub-tree and' +
      '  smaller than the keys in all nodes in that node\'s right sub-tree.' +
      '</p>'
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
    ],
    helpText:
      '<p>' +
      '  <strong>Tip:</strong> Click <em>Insert a random item</em>' +
      '  repeatedly to quickly build an AVL tree.' +
      '</p>' +
      '<hr>' +
      '<p>' +
      '  An <a href="http://en.wikipedia.org/wiki/AVL_tree">AVL tree</a>' +
      '  (Georgy Adelson-Velsky and Landis\' tree, named after' +
      '  the inventors) is a' +
      '  <a href="http://en.wikipedia.org/wiki/Self-balancing_binary_search_tree">' +
      '  self-balancing binary search tree</a>.' +
      '</p>' +
      '<p>' +
      '  In an AVL tree, the heights of the two child subtrees of any node' +
      '  differ by at most one; if at any time they differ by more than one,' +
      '  rebalancing is done to restore this property.' +
      '</p>' +
      '<p>' +
      '  Lookup, insertion, and deletion all take <em>O(log n)</em> time in' +
      '  both the average and worst cases, where <em>n</em> is the number of' +
      '  nodes in the tree prior to the operation. Insertions and deletions' +
      '  may require the tree to be rebalanced by one or more tree rotations.' +
      '</p>' +
      '<p>' +
      '  The <em>balance factor</em> of each node, i.e. the difference' +
      '  between the heights of its left and right subtrees, is shown in' +
      '  parentheses next to its key. Note that in an AVL tree, any node' +
      '  can only have a balance factor of -1, 0 or 1.' +
      '</p>'
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
    ],
    helpText:
      '<p>' +
      '  <strong>Tip:</strong> Click <em>Push a random item</em>' +
      '  repeatedly to quickly build a heap.' +
      '</p>' +
      '<hr>' +
      '<p>' +
      '  A <a href="http://en.wikipedia.org/wiki/Binary_heap">heap</a> is an' +
      '  array object that can be seen as a nearly complete binary tree. In a' +
      '  heap, either every node has a key smaller or equal than all the' +
      '  nodes of the subtree rooted at that node (this kind of heap is' +
      '  called a <em>min heap</em>) or every node has a key greater or equal' +
      '  than all the nodes of the subtree rooted at that node (<em>max' +
      '  heap</em>).' +
      '</p>' +
      '<p>' +
      '  The root node, thus, contains the smallest key in the tree in the' +
      '  case of a min heap, or greatest in the case of a max heap. This' +
      '  allows querying the smallest/greater key in constant time. Insertion' +
      '  and deletion take <em>O(log n)</em> time in both the average and' +
      '  worst cases, where <em>n</em> is the number of nodes in the heap' +
      '  prior to the operation.' +
      '</p>' +
      '<p>' +
      '  The heap implemented here happens to be a min heap.' +
      '</p>' +
      '<p>' +
      '  An example min heap and its corresponding binary tree are pictured' +
      '  below.' +
      '<p>' +
      '<pre>1 2 6 4 3 10 8 9 7 5</pre>' +
      '<pre>\n' +
      '      ..1..\n' +
      '     /     \\\n' +
      '   .2..     6\n' +
      '  /    \\   / \\\n' +
      '  4    3  10 8\n' +
      ' / \\   /\n' +
      '9  7  5\n' +
      '</pre>'
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
    ],
    helpText:
      '<p>' +
      '  <strong>Tip:</strong> Click <em>Insert a random item</em>' +
      '  repeatedly to quickly build a skip list.' +
      '</p>' +
      '<hr>' +
      '<p>' +
      '  A <a href="http://en.wikipedia.org/wiki/Skip_list">skip list</a> is' +
      '  an ordered <a href="http://en.wikipedia.org/wiki/Linked_list">linked' +
      '  list</a> that allows fast search by maintaining a linked hierarchy' +
      '  of subsequences.' +
      '</p>' +
      '<p>' +
      '  A skip list is built in layers. The bottom layer is an ordinary' +
      '  ordered linked list. Each higher layer acts as an "express lane" for' +
      '  the lists below, where an element in layer <em>i</em> appears in' +
      '  layer <em>i+1</em> with some fixed probability <em>p</em> (two' +
      '  commonly used values for <em>p</em> are 1/2 or 1/4).' +
      '</p>' +
      '<p>' +
      '  A search for a target element begins at the head element in the top' +
      '  list, and proceeds horizontally until the current element is greater' +
      '  than or equal to the target. If the current element is equal to the' +
      '  target, it has been found. If the current element is greater than' +
      '  the target, or the search reaches the end of the linked list, the' +
      '  procedure is repeated after returning to the previous element and' +
      '  dropping down vertically to the next lower list.' +
      '</p>' +
      '<p>' +
      '  Lookup, insertion, and deletion all take <em>O(log n)</em> time in' +
      '  the average case and <em>O(n)</em> in the worst case, where' +
      '  <em>n</em> is the number of items in the skip list prior to the' +
      '  operation.' +
      '</p>'
  }
];
