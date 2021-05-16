#ifndef _Agent_QueryTable_h_
#define _Agent_QueryTable_h_


// Theory: http://www.saedsayad.com/decision_tree.htm

NAMESPACE_TOPSIDE_BEGIN

template <class T>
class QueryTable {
	
	Array<Vector<T> > predictors;
	Vector<T> target;
	Vector<double> gains;
	
	Vector<String> predictor_names;
	String target_name;
	
public:
	
	QueryTable() {}
	
	Vector<T>& AddPredictor(const String& name) {predictor_names.Add(name); return predictors.Add();}
	
	
	void AddValue(int i, const T& value) {predictors[i].Add(value);}
	void AddTargetValue(const T& value) {target.Add(value);}
	
	const Vector<double>& GetInfoGains() const {return gains;}
	
	int GetLargestInfoGainPredictor() {
		
		// Prepare function
		gains.Clear();
		ASSERT(predictors.GetCount());
		ASSERT(target.GetCount());
		ASSERT(predictors[0].GetCount() == target.GetCount());
		
		// Find all unique target values, and count them
		VectorMap<T, int> target_count;
		for(int i = 0; i < target.GetCount(); i++) {
			T& t = target[i];
			target_count.GetAdd(t, 0)++;
		}
		
		// Count total (some values could have been skipped as invalid)
		double total = 0;
		for(int i = 0; i < target_count.GetCount(); i++)
			total += target_count[i];
		
		// Calculate entropy
		double entropy = 0;
		for(int i = 0; i < target_count.GetCount(); i++)  {
			double part = target_count[i] * 1.0 / total;
			entropy -= part * log2((double)part);
		}
		
		// Loop over all predictors
		for(int i = 0; i < predictors.GetCount(); i++) {
			Vector<T>& vec = predictors[i];
			
			VectorMap<T, VectorMap<T, int> > pred_counts;
			
			double pred_total = 0;
			for(int j = 0; j < vec.GetCount(); j++) {
				// Get predictor value and target value
				T& c = vec[j];
				T& t = target[j];
				
				// Get map by predictor value
				VectorMap<T, int>& pred_target_count = pred_counts.GetAdd(c);
				
				// Increase target count with this predictor value by one
				pred_target_count.GetAdd(t, 0)++;
				
				pred_total += 1;
			}
			
			// Loop over all unique values in the column
			double pred_entropy = 0;
			for(int j = 0; j < pred_counts.GetCount(); j++) {
				VectorMap<T, int>& pred_target_count = pred_counts[j];
				
				// Sum total value count in the table with this unique predictor category
				int pred_cat_total = 0;
				for(int k = 0; k < pred_target_count.GetCount(); k++)
					pred_cat_total += pred_target_count[k];
				
				// Calculate entropy for predictor category
				double pred_cat_entropy = 0;
				for(int k = 0; k < pred_target_count.GetCount(); k++) {
					double part = pred_target_count[k] * 1.0 / pred_cat_total;
					pred_cat_entropy -= part * log2((double)part);
				}
				pred_entropy += (double)pred_cat_total / pred_total * pred_cat_entropy;
			}
			
			// Calculate information gain value with this predictor in the current dataset
			double gain = entropy - pred_entropy;
			gains.Add(gain);
		}
		
		// Find the maximum information gain predictor
		double max_gain = -DBL_MAX;
		int max_id = -1;
		for(int i = 0; i < gains.GetCount(); i++) {
			if (gains[i] > max_gain) {
				max_gain = gains[i];
				max_id = i;
			}
		}
		
		return max_id;
	}
};

NAMESPACE_TOPSIDE_END

#endif
