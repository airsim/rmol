package org.amadeus.jrmol.bom;

import java.util.Collections;
import java.util.Vector;

/** 
 * Holder of a PartialSumList object (for memory allocation and
 * recollection purposes).
 */
public class BomPartialSumHolder extends BomAbstract {

	/** 
	 * The vector of (K) partial sums.
	 */
	private PartialSumList _partialSumList = null;
	
	public BomPartialSumHolder() {
		_partialSumList = new PartialSumList();
	}

	public BomPartialSumHolder(final int K) {
		_partialSumList = new PartialSumList(K);
	}

	/** 
	 * Get the k-th element (partial sum).
	 */
	public final double getPartialSum(final int k) {
		return _partialSumList.get(k);
	}

	/** 
	 * Add an element (partial sum).
	 */
	public void addPartialSum(final double iPartialSum) {
		_partialSumList.add(iPartialSum);
	}

	/** 
	 * Sort the elements (partial sums).
	 */
	public void sort() {
		Collections.sort(_partialSumList);
	}
	
	private class PartialSumList extends Vector<Double> {
		private PartialSumList() {}
		
		private PartialSumList(final int K) {
			super(K);
		}
	}
}
