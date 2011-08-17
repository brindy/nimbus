//
// Copyright 2011 Jeff Verkoeyen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <Foundation/Foundation.h>

#if NS_BLOCKS_AVAILABLE
typedef UITableViewCell* (^NITableViewModelCellForIndexPathBlock)(UITableView* tableView, NSIndexPath* indexPath, id object);
#endif // #if NS_BLOCKS_AVAILABLE

@protocol NITableViewModelDelegate;

// Classes used when creating NITableViewModels.
@class NITableViewModelFooter;  // Provides the information for a footer.

/**
 * A non-mutable table view model that complies to the UITableViewDataSource protocol.
 *
 * This model allows you to easily create a data source for a UITableView without having to
 * implement the UITableViewDataSource methods in your UITableViewController.
 *
 * This base class is non-mutable, much like an NSArray. You must initialize this model with
 * the contents when you create it.
 *
 *      @ingroup TableViewModels
 */
@interface NITableViewModel : NSObject <UITableViewDataSource> {
@private
  // Compiled Information
  NSArray* _sections;  // Array of internal section objects

  // Creating Table View Cells
  id<NITableViewModelDelegate> _delegate;

#if NS_BLOCKS_AVAILABLE
  NITableViewModelCellForIndexPathBlock _createCellBlock;
#endif // #if NS_BLOCKS_AVAILABLE
}

#pragma mark Creating Table View Models

// Designated initializer.
- (id)initWithDelegate:(id<NITableViewModelDelegate>)delegate;
- (id)initWithListArray:(NSArray *)sectionedArray delegate:(id<NITableViewModelDelegate>)delegate;
- (id)initWithSectionedArray:(NSArray *)sectionedArray delegate:(id<NITableViewModelDelegate>)delegate;

#pragma mark Accessing Objects

- (id)objectAtIndexPath:(NSIndexPath *)indexPath;

#pragma mark Creating Table View Cells

@property (nonatomic, readwrite, assign) id<NITableViewModelDelegate> delegate;

#if NS_BLOCKS_AVAILABLE
// If both the delegate and this block are provided, cells returned by this block will be used
// and the delegate will not be called.
@property (nonatomic, readwrite, copy) NITableViewModelCellForIndexPathBlock createCellBlock;
#endif // #if NS_BLOCKS_AVAILABLE

@end

/**
 * A protocol for NITableViewModel to fetch rows to be displayed for the table view.
 */
@protocol NITableViewModelDelegate <NSObject>

@required

/**
 * Fetches a table view cell at a given index path with a given object.
 *
 * The implementation of this method will generally use object to customize the cell.
 */
- (UITableViewCell *)tableViewModel: (NITableViewModel *)tableViewModel
                   cellForTableView: (UITableView *)tableView
                        atIndexPath: (NSIndexPath *)indexPath
                         withObject: (id)object;

@end

/**
 * An object used in sectioned arrays to denote a section footer title.
 *
 * Meant to be used in a sectioned array for NITableViewModel.
 *
 * <h3>Example</h3>
 *
 * @code
 *  [NITableViewModelFooter footerWithTitle:@"Footer"],
 * @endcode
 */
@interface NITableViewModelFooter : NSObject {
@private
  NSString* _title;
}

+ (id)footerWithTitle:(NSString *)title;
- (id)initWithTitle:(NSString *)title;

@property (nonatomic, readwrite, copy) NSString* title;

@end

/** @name Creating Table View Models */

/**
 * Initializes a newly allocated static model with the given delegate and empty contents.
 *
 * This method can be used to create an empty model.
 *
 *      @fn NITableViewModel::initWithDelegate:
 */

/**
 * Initializes a newly allocated static model with the contents of a list array.
 *
 * A list array is a one-dimensional array that defines a flat list of rows. There will be
 * no sectioning of contents in any way.
 *
 * <h3>Example</h3>
 *
 * @code
 * NSArray* contents =
 * [NSArray arrayWithObjects:
 *  [NSDictionary dictionaryWithObject:@"Row 1" forKey:@"title"],
 *  [NSDictionary dictionaryWithObject:@"Row 2" forKey:@"title"],
 *  [NSDictionary dictionaryWithObject:@"Row 3" forKey:@"title"],
 *  nil];
 * [[NIStaticTableViewModel alloc] initWithListArray:contents delegate:self];
 * @endcode
 *
 *      @fn NITableViewModel::initWithListArray:delegate:
 */

/**
 * Initializes a newly allocated static model with the contents of a sectioned array.
 *
 * A sectioned array is a one-dimensional array that defines a list of sections and each
 * section's contents. Each NSString begins a new section and any other object defines a
 * row for the current section.
 *
 * <h3>Example</h3>
 *
 * @code
 * NSArray* contents =
 * [NSArray arrayWithObjects:
 *  @"Section 1",
 *  [NSDictionary dictionaryWithObject:@"Row 1" forKey:@"title"],
 *  [NSDictionary dictionaryWithObject:@"Row 2" forKey:@"title"],
 *  @"Section 2",
 *  // This section is empty.
 *  @"Section 3",
 *  [NSDictionary dictionaryWithObject:@"Row 3" forKey:@"title"],
 *  nil];
 * [[NIStaticTableViewModel alloc] initWithSectionedArray:contents delegate:self];
 * @endcode
 *
 *      @fn NITableViewModel::initWithSectionedArray:delegate:
 */


/** @name Accessing Objects */

/**
 * Returns the object at the given index path.
 *
 * If no object exists at the given index path (an invalid index path, for example) then nil
 * will be returned.
 *
 *      @fn NITableViewModel::objectAtIndexPath:
 */


/** @name Creating Table View Cells */

/**
 * A delegate used to fetch table view cells for the data source.
 *
 *      @fn NITableViewModel::delegate
 */

#if NS_BLOCKS_AVAILABLE

/**
 * A block used to create a UITableViewCell for a given object.
 *
 *      @fn NITableViewModel::createCellBlock
 */

#endif // #if NS_BLOCKS_AVAILABLE
