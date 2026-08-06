
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class CharCounter {

	private int[] counts = new int[256];
	private int total = 0;
	private boolean useLowerCase = true;
	private boolean useUpperCase = false;


	public void addToCount(String text) {

		if (useLowerCase) text = text.toLowerCase();
		if (useUpperCase) text = text.toUpperCase();

		char[] chars = text.toCharArray();

		for(char c : chars) {
			counts[c]++;
		}

		total = 0;
		for(int count : counts) 
			total += count;
	}


	public List<CharCount> getList() {
		List<CharCount> countList = new ArrayList<CharCount>();

		for(int i=0; i<counts.length; i++) {

			boolean isLetter = i >='a' && i <= 'z' || i >='A' && i <= 'Z'; 
			boolean isNum = i >='0' && i <= '9'; 
			boolean isPunctiation = ".,?!;:()".indexOf((char)i) != -1;
			boolean ok = isLetter || isNum || i==32 || isPunctiation;


			if (counts[i] > 0 && ok){
				char c = (char)i;
				double percent = counts[i] / (double)total * 100;
				CharCount cc = new CharCount(c, counts[i], percent);

				countList.add(cc);
			}
		}

		Collections.sort(countList, (a, b) -> b.getCount() - a.getCount());

		return countList;
	}


	int[] getCounts() {
		return this.counts;
	}

	public void showList() {
		List<CharCount> countList = getList();

		for(CharCount cc : countList) {
			System.out.printf("'%c' : %d - %.2f\n", cc.getChar(), cc.getCount(), cc.getPercent());
		}
		
		System.out.printf("Total %d\n", total);
	}

	public void showCounts() {

		for(int i=0; i<counts.length; i++) {
			if (i>=32 && counts[i] > 0) {
				char c = (char)i;
				System.out.printf("'%c' : %d \n", c, counts[i]);
			}
		}
	}

	public void setUseUpperCase(boolean value) {
		this.useUpperCase = value;
		this.useLowerCase = !value && this.useLowerCase;
	}

	public void setUseLowerCase(boolean value) {
		this.useLowerCase = value;
		this.useUpperCase = !value && this.useUpperCase;
	}

}





