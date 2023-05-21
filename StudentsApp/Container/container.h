/*
 * container.h
 *
 *  Created on: 21 avr. 2022
 *      Author: Garnier
 */

/**
 * @brief Function pointers definition.
 */
typedef void*(*t_ptfV)(void*);			// For functions like:  void*()(void*)
typedef void*(*t_ptfVV)(void*, void*);	// For functions like:  void*()(void*, void*)


/**
 * @brief Container type definition: "hidden structure" or "incomplete structure" definition.
 */
typedef struct s_container t_container;

/**
 * @brief  Container public functions declaration.
 */

/**
 * @brief Container "constructor".
 *
 * @param [in] pDeleteItemFunc 	function pointer to the function responsible of
 * 								properly deleting items in stored in container.
 * @return t_container* pointer on the newly created container.
 */
t_container*ContainerNew(t_ptfV pDeleteItemFunc);

/**
 * @brief  Container "destructor".
 *
 * @param [in] pContainer pointer to the container to destroy.
 * @return t_container* NULL.
 */
t_container*ContainerDel(t_container *pContainer);

/**
 * @brief 	Flushing the container by deleting all items and nodes.
 * 			The container structure is not destroyed !
 *
 * @param [in] pContainer pointer to the container to flush.
 * @return t_container* the flushed container.
 */
t_container*ContainerFlush(t_container *pContainer);

/**
 * @brief Returns the number of elements in container.
 *
 * @param pContainer pointer to the container to get cardinal.
 * @return size_t number of elements.
 */
size_t ContainerCard(const t_container*pContainer);

/**
 * @brief Append a item at the end of the container.
 *
 * @param [in] pContainer pointer to the container to append to.
 * @param [in] pItem pointer to the item to append.
 * @return void* pointer to the item that was appended.
 */
void*ContainerPushback(t_container*pContainer, void*pItem);

/**
 * @brief Append a item at the beginning of the container.
 *
 * @param [in] pContainer pointer to the container to append to.
 * @param [in] pItem pointer to the item to append.
 * @return void* pointer to the item that was appended.
 */
void*ContainerPushfront(t_container*pContainer, void*pItem);

/**
 * @brief Insert a item in the container at index.
 *
 * @param [in] pContainer pointer to the container to insert into.
 * @param [in] pItem pointer to the item to insert.
 * @param [in] sAt index to insert at.
 * @return void* pointer to the item that was inserted.
 */
void*ContainerPushat(t_container*pContainer, void*pItem, size_t szAt);

/**
 * @brief Get the last item from the container. The item persists in
 * 		  the container!
 *
 * @param pContainer pointer to the container to get from.
 * @return void* pointer to the got item.
 */
void*ContainerGetback(const t_container*pContainer);

/**
 * @brief Get the first item from the container. The item persists in
 * 		  the container!
 *
 * @param pContainer pointer to the container to get from.
 * @return void* pointer to the got item.
 */
void*ContainerGetfront(const t_container*pContainer);

/**
 * @brief Get the item stored at index from the container. The
 * 		  item persists in the container!
 *
 * @param [in] pContainer pointer to the container to get from.
 * @param [in] sAt index to get from.
 * @return void* pointer to the got item.
 */
void*ContainerGetat(const t_container*pContainer, size_t szAt);

/**
 * @brief Extract the last item from the container, and return it to caller.
 * 		  The item is removed from the container and the corresponding node is deleted.
 * @param pContainer pointer to the container to extract from.
 * @return void* pointer to the popped item.
 */
void*ContainerPopback(t_container*pContainer);

/**
 * @brief Extract the first item from the container, and return it to caller.
 * 		  The item is removed from the container and the corresponding node is deleted.
 * @param [in] pContainer pointer to the container to extract from.
 * @return void* pointer to the popped item.
 */
void*ContainerPopfront(t_container*pContainer);

/**
 * @brief Extract the item located at index from the container, and return it to caller.
 * 		  The item is removed from the container and the corresponding node is deleted.
 * @param [in] pContainer pointer to the container to extract from.
 * @param [in] sAt index to extract from.
 * @return void* pointer to the popped item.
 */
void*ContainerPopat(t_container*pContainer, size_t szAt);

/**
 * @brief Parsing the container from front to back, and for each item, calling
 * 		  the parsing function with parameters the pointer to the corresponding
 * 		  item and the pParam parameter.
 * 		  The parsing is stopped if the parsing function returns a non null value,
 * 		  and in this case, the function returns the corresponding item to the caller.
 *
 * @param [in] pContainer pointer to the container to parse.
 * @param [in] pParseFunc pointer to the called function for each parsed item.
 * @param [in] pParam parameter directly passed to the called function during parsing.
 * @return void* NULL in case of a complete parsing,
 * 				 pointer to the item in case of interrupted parsing.
 */
void*ContainerParse(const t_container*pContainer, t_ptfVV pParseFunc, void*pParam);

/**
 * @brief Parsing the container from front to back, and for each item, calling
 * 		  the parsing function with parameters the pointer to the corresponding
 * 		  item and the pParam parameter.
 * 		  In case of a non null return value from called function, the item and the
 * 		  corresponding node are destroyed. The parsing is then resumed to the next
 * 		  item and the same scenario takes place, until container back is reached.
 *
 * @param [in] pContainer pointer to the container to parse.
 * @param [in] pParseFunc pointer to the called function for each parsed item.
 * @param [in] pParam parameter directly passed to the called function during parsing.
 * @return void* NULL (complete parsing).
 */
void*ContainerParseDelIf(t_container*pContainer, t_ptfVV pParseFunc, void*pParam);

/**
 * @brief Parsing the container A, and for each of its items, calls the intersection
 * 		  function with each item of the container B. In case of matched intersection,
 * 		  both item and node in container A are destroyed, and both item and node
 * 		  in container B are also destroyed. In this case, the parsing is resumed
 * 		  to the next item of container A, and the same scenario takes place by parsing
 * 		  container B from his front to back. Parsing ending when all items in each
 * 		  container has been intersected with each other.
 *
 * @param [in] pContainerA pointer the the first container to intersect.
 * @param [in] pContainerB pointer the the second container to intersect.
 * @param [in] pIntersectFunc pointer to the called intersect function for each parsed items.
 * @param [in] pCallbackFunc pointer to the callback function in case of intersection.
 * @param [in] pParam parameter directly passed to the callback function.
 * @return void*  NULL (complete parsing).
 */
void*ContainerIntersectDelIf(t_container*pContainerA, t_container*pContainerB, t_ptfVV pIntersectFunc,t_ptfVV pCallbackFunc, void*pParam);



void*ContainerInsert(t_container*pContainer, t_ptfVV pPredicaFunc, void*pItem);

void*ContainerInsertUnic(t_container*pContainer, t_ptfVV pPredicaFunc, void*pItem);

void*ContainerSerialize(t_container*pContainer, t_ptfVV pSerializeFunc);

void*ContainerDeserialize(t_container*pContainer, t_ptfVV pDeserializeFunc);
