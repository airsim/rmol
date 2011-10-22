import org.amadeus.jrmol.bom.BomBucket;
import org.amadeus.jrmol.bom.BomBucketHolder;
import org.amadeus.jrmol.bom.BomDemand;
import org.amadeus.jrmol.command.CmdOptimizeProtectionsByMcIntegration;
import org.amadeus.jrmol.field.FldDistributionParameters;
import org.amadeus.jrmol.field.FldYieldRange;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try 
		{
			// Number of random draws to be generated (best if greater than 100)
			int K = 100000;
		
			// Cabin Capacity (it must be greater then 100 here)
			double cabinCapacity = 500.0;
			
			// Input file name
			String inputFileName = "class.csv";
			boolean hasInputFile = false;

			if (args.length >= 1 && args[1] != null) {
				K = Integer.parseInt(args[1]);
			}

			if (args.length >= 2 && args[2] != null) {
				cabinCapacity = Double.parseDouble(args[2]);
			}

			if (args.length >= 3 && args[3] != null) {
				inputFileName = new String(args[3]);
				hasInputFile = true;
			}

			// Initialise the list of classes/buckets
			BomBucketHolder aBucketHolder = new BomBucketHolder(cabinCapacity);

			if (hasInputFile) 
			{
				// TODO
				return;

			} 
			else 
			{
				// No input file has been provided. So, process a sample.

				// STEP 0.
				// List of demand distribution parameters (mean and standard deviation)

				// Class/bucket 1: N (20, 9), p1 = 100
				final FldYieldRange aYieldRange1 = new FldYieldRange(100.0);
				final FldDistributionParameters aDistribParams1 = new FldDistributionParameters(20, 9);
				final BomDemand aDemand1 = new BomDemand(aDistribParams1, aYieldRange1);
				
				BomBucket aBucket1 = new BomBucket(aYieldRange1, aDemand1);
				aBucketHolder.addBucket(aBucket1);

				// Class/bucket 2: N (45, 12), p2 = 70
				final FldYieldRange aYieldRange2 = new FldYieldRange(70.0);
				final FldDistributionParameters aDistribParams2 = new FldDistributionParameters(45, 12);
				final BomDemand aDemand2 = new BomDemand(aDistribParams2, aYieldRange2);
				
				BomBucket aBucket2 = new BomBucket(aYieldRange2, aDemand2);
				aBucketHolder.addBucket(aBucket2);

				// Class/bucket 3: no need to define a demand distribution, p3 = 42
				final FldYieldRange aYieldRange3 = new FldYieldRange(42.0);
				BomBucket aBucket3 = new BomBucket(aYieldRange3);
				aBucketHolder.addBucket(aBucket3);
			}

			// Calculate the optimal protections by the Monte Carlo Integration approach
			long startTime = System.currentTimeMillis();
			CmdOptimizeProtectionsByMcIntegration.optimize(K, cabinCapacity, aBucketHolder);
			long endTime = System.currentTimeMillis();
			
			// Display
			System.out.println(aBucketHolder);
			
			System.out.println("Done in " + (endTime - startTime) + "ms");

		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}	
	}
}
