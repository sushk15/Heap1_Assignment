#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "appconst.h"
#include "heap.h"

static void _swap_(int32_t *data1, int32_t *data2){
    int32_t temp;
    temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

uint32_t  heap_size(Heap *heap){

    assert ( heap->size > 0 && heap->size < HEAP_MAX_SIZE );
    return heap->size;

}

static void _heapify_ (int32_t data[], uint32_t len, uint32_t parent){
    assert ( len > 0 && len < HEAP_MAX_SIZE && parent > 0);

    uint32_t child = 2 * parent;

    while ( child <= len ){
        if ( child + 1 <= len ){
            if ( data[child+1] > data[child]){
                ++child;
            }
        }
        if ( data[parent] > data[child] ){
            break;
        }
        _swap_(&data[parent], &data[child]);
        parent = child;
        child = 2 * parent;
    }

}

static void _test_heap_(int32_t  data[], uint32_t len){

    for ( uint32_t child = len; child > 1 ; --child){
        assert(data[child] <= data[child/2]);
    }
}

Heap* heap_test(Heap *heap){
    assert ( heap->size > 0 && heap->size < HEAP_MAX_SIZE );

    _test_heap_(heap->data, heap->size);

    return heap;
}

Heap heap_new(int32_t data[], uint32_t len){
    assert( len > 0 && len < HEAP_MAX_SIZE );

    Heap heap;

    for (uint32_t idx = len/2; idx > 0 ; --idx){
        _heapify_(data, len , idx);
    }
    heap.size = len;
    memcpy(heap.data, data, (len+1) * sizeof(int32_t));
    _test_heap_(heap.data, heap.size);

    return heap;
}

Heap* heap_sort(Heap *heap){
    assert ( heap->size > 0 && heap->size < HEAP_MAX_SIZE );

    uint32_t idx = heap->size;

    for (idx = heap->size; idx > 1; idx--){
        _swap_(&heap->data[idx], &heap->data[1]);
        _heapify_(heap->data, idx-1, 1);
    }
    return heap;
}

Heap*     heap_insert(Heap *heap, int32_t key){
    assert ( heap->size > 0 && heap->size < HEAP_MAX_SIZE );

    // Increase the size of Heap by 1
    heap->size = heap->size + 1;

    // Insert the element at end of Heap
    heap->data[heap->size] = key;

    //heapify after inserting new element
    _heapify_(heap->data, heap->size, heap->size);

    return heap;
}

int32_t   heap_extract_max(Heap *heap){  //delete the max elem from heap
    assert ( heap->size > 0 && heap->size < HEAP_MAX_SIZE );

    int32_t max = heap->data[1];

    // Get the last element
    int32_t last = heap->data[heap->size];

    // Replace root with first element
    heap->data[1] = last;

    // Decrease size of heap by 1
    heap->size = heap->size-1;

    // heapify the root node
    _heapify_(heap->data, heap->size, 1);

    return max;
}

int32_t   heap_get_max(Heap *heap){
    assert ( heap->size > 0 && heap->size < HEAP_MAX_SIZE );

    int32_t max = heap->data[1];
    return max;
}
