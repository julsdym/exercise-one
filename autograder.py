import subprocess

FILE_NAME = "hw1"

def compile_program():
	compile_result = subprocess.run(["gcc", "-fsanitize=address", FILE_NAME+".c", "-o", FILE_NAME], capture_output=True, text=True)
	if compile_result.returncode != 0:
		print("Compilation failed:", compile_result.stderr)
		return False
	return True

def run_test(test_number, test_input, expected_output):
	process = subprocess.Popen(["./"+FILE_NAME, *(test_input.split(' '))], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	stdout, stderr = process.communicate()

	print(f"Test Case {test_number}: Input = {test_input}", end=" ")

	if stdout.strip() == expected_output.strip() or stderr.strip() == expected_output.strip():
		print("✓ Passed")
		return True
	else:
		print("✗ Failed")
		print(f"   Expected: {expected_output}")
		print(f"   Got: {stdout.strip() if stdout != '' else stderr.strip()}")
		return False

def main():
	if not compile_program():
		return

	test_cases = [
		(1, "this is an incorrect way to pass arguments", "Usage: ./hw1 {transformArray|numDuplicates|replaceLastNRandom}"),

		(2, "transformArray 3 5 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15", "4 5 3 1 2 \n9 10 8 6 7 \n14 15 13 11 12 \n"),
		(3, "transformArray 4 3 1 2 3 4 5 6 7 8 9 10 11 12", "3 2 1 \n6 5 4 \n9 8 7 \n12 11 10 \n"),
		(4, "transformArray 3 7 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21", "5 6 7 4 1 2 3 \n12 13 14 11 8 9 10 \n19 20 21 18 15 16 17 \n"),

		(5, "numDuplicates 4 1 recordA 1970 2 recordB 1968 3 recordA 1970 4 recordC 1970", "1"),
		(6, "numDuplicates 5 1 Thriller 1982 2 Thriller 1982 3 BillieJean 1982 4 Thriller 1982 5 BillieJean 1982", "3"),
		(7, "numDuplicates 4 1 BohemianRhapsody 1975 2 WeWillRockYou 1977 3 SomebodyToLove 1976 4 WeAreTheChampions 1977", "0"),

		(8, "replaceLastNRandom 2 5 10 20 30 40 50", "10 20 30 383100999 858300821"),
		(9, "replaceLastNRandom 3 6 5 15 25 35 45 55", "5 15 25 383100999 858300821 357768173"),
		(10, "replaceLastNRandom 1 4 7 8 9 10", "7 8 9 383100999"),
	]

	all_passed = True
	for test_number, test_input, expected_output in test_cases:
		if not run_test(test_number, test_input, expected_output):
			all_passed = False

	if all_passed:
		print("All tests passed successfully!")
	else:
		print("Some tests failed.")

if __name__ == "__main__":
	main()
